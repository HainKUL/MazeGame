#include "scene.h"
#include <QDebug>

Scene::Scene(std::shared_ptr<Model> model,QObject *parent):QGraphicsScene(parent),myModel{model}
{
    proView = new ProtagonistView();
    addEnvironment();
    addProtagonist();
    addHP();
    addEnemies();

    //connect protagnisit move
    connect(this->myModel.get(),SIGNAL(refreshPathView()),this,SLOT(addPath()));
    connect(this->myModel->myProtagonist.get(), SIGNAL(posChanged(int, int)), this, SLOT(ProtagonistViewChanged_slot(int, int)));
}

Scene::~Scene()
{
    std::vector<QGraphicsPixmapItem*>().swap(this->pathView);
}

void Scene::addPath()
{
    auto path = myModel->getPathfinder()->getPath();
    for(int i=1;i<path.size();i++)
    {
        QGraphicsPixmapItem * pa = new QGraphicsPixmapItem();
        pa->setPixmap(QPixmap(":/images/path.png"));
        pa->setX(path[i].x*50);
        pa->setY(path[i].y*50);
        pathView.push_back(pa);
        addItem(pa);
    }
}


void Scene::ProtagonistViewChanged_slot(int x, int y)
{
    //qDebug()<<"receive signal"<<x<<","<<y;
    DIRECTION d;
    if(x>((proView->x)()/len)){
        d = RIGHT;
    }else if(x<((proView->x)()/len)){
        d = LEFT;
    }else if (y>((proView->y)()/len)) {
        d = DOWN;
    }else if(y<((proView->y)()/len)){
        d = UP;
    }else {
        d = NOCHANGE;
    }
    proView->move(x,y,d);
    if(tracked){
        if(step>0){
            step--;
        }else {
            emit centerMe();
            step=10;
        }
    }
}

void Scene::addEnvironment()
{
    int row_of_world = myModel->myWorld->getRows();
    int col_of_world = myModel->myWorld->getCols();
    for (int row=0; row < row_of_world; row++) {
        for(int col = 0; col < col_of_world; col++){
            EnvironmentView *envi = new EnvironmentView(myModel->myEnvironment.at(col+row*col_of_world)->getValue());
            connect(myModel->myEnvironment.at(col+row*col_of_world).get(), SIGNAL(poiValueChanged()), envi, SLOT(poisoned()));
            envi->setX(len*col);
            envi->setY(len*row);
            enrvironmentViews.push_back(envi);
            addItem(envi);
        }
    }
}

void Scene::addHP()
{
    for (int i=0; i < myModel->myHP.size(); i++) {
            HealthPackView *hp = new HealthPackView();
            connect(myModel->myHP.at(i).get(), SIGNAL(used_signal()), hp, SLOT(used_slot()));
            hp->setX(len*myModel->myHP.at(i)->getXPos());
            hp->setY(len*myModel->myHP.at(i)->getYPos());
            hps.push_back(hp);
            addItem(hp);
    }
}

void Scene::addEnemies()
{
    for (int i=0; i < myModel->myEnemies.size(); i++) {
        if(dynamic_cast<PEnemy *>(myModel->myEnemies.at(i).get()))
        {//penemy
            PEnemyView *ene = new PEnemyView();
            connect(myModel->myEnemies.at(i).get(), SIGNAL(dead()), ene, SLOT(dead_slot()));
            ene->setX(len*myModel->myEnemies.at(i)->getXPos());
            ene->setY(len*myModel->myEnemies.at(i)->getYPos());
            penemies.push_back(ene);
            addItem(ene);
        }
        else if(dynamic_cast<XEnemy *>(myModel->myEnemies.at(i).get()))
        {//xenemy
            auto xe = dynamic_cast<XEnemy *>(myModel->myEnemies.at(i).get());
            XEnemyView *xeView = new XEnemyView();
            connect(xe, SIGNAL(dead()), xeView, SLOT(dead_slot()));
            connect(xe, SIGNAL(positionChanged(int,int,DIRECTION)), xeView, SLOT(move(int,int,DIRECTION)));
            xeView->setX(len*myModel->myEnemies.at(i)->getXPos());
            xeView->setY(len*myModel->myEnemies.at(i)->getYPos());
            xenemies.push_back(xeView);
            addItem(xeView);
        }
        else{//normal enemy
            EnemyView *ene = new EnemyView();
            connect(myModel->myEnemies.at(i).get(), SIGNAL(dead()), ene, SLOT(dead_slot()));
            ene->setX(len*myModel->myEnemies.at(i)->getXPos());
            ene->setY(len*myModel->myEnemies.at(i)->getYPos());
            enemies.push_back(ene);
            addItem(ene);
        }
    }
}

bool Scene::getPause() const
{
    return pause;
}

void Scene::setPause(bool value)
{
    pause = value;
}

void Scene::addProtagonist()
{
    proView->setX(len*myModel->myProtagonist->getXPos());
    proView->setY(len*myModel->myProtagonist->getYPos());
    addItem(proView);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(pause)
        return;
    for(auto paV:this->pathView){
                this->removeItem(paV);
            }
            std::vector<QGraphicsPixmapItem*>().swap(this->pathView);
    int x = static_cast<int>(event->scenePos().x()/50);
    int y = static_cast<int>(event->scenePos().y()/50);
    myModel->clickedPos(x,y);
    qDebug()<<x<<y;
}


bool Scene::getTracked() const
{
    return tracked;
}

void Scene::setTracked(bool value)
{
    tracked = value;
}
