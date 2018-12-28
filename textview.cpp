#include "textview.h"
#include <iostream>

TextView::TextView(std::shared_ptr<Model> &m): model{m}
{
    //create protag textview
    tvProtag = std::make_shared<ProtagonistTextView>(model->myProtagonist->getXPos(),model->myProtagonist->getYPos());

    //connect protag model signal and slot defined in textview class, update textui
    connect(model->myProtagonist.get(),SIGNAL(posChanged(int,int)),this,SLOT(updateProtagPosition(int,int)));

    rows = model->myWorld->getRows();
    cols = model->myWorld->getCols();

    //create enemy textview for each enemy, and connect
    for(auto & e:model->myEnemies)
    {
        auto pe = dynamic_cast<PEnemy *>(e.get());
        auto xe = dynamic_cast<XEnemy *>(e.get());
        if(pe)
        {//if penemy
            auto tvPEnemy = std::make_shared<PEnemyTextView>(pe->getXPos(),pe->getYPos());
            tvPEnemies.push_back(tvPEnemy);
            connect(pe,SIGNAL(dead()),tvPEnemy.get(),SLOT(dead_slot()));
        }
        else if(xe)
        {//if xenemys
            auto tvXEnemy = std::make_shared<XEnemyTextView>(xe->getXPos(),xe->getXPos());
            tvXEnemies.push_back(tvXEnemy);
            //connect penemy textview
            connect(xe,SIGNAL(positionChanged(int,int,DIRECTION)),tvXEnemy.get(),SLOT(updateXEnemyPosition(int,int)));
            connect(tvXEnemy.get(),SIGNAL(updateXEnemyTV_signal(int,int,int,int,std::string)),this,SLOT(updateXEnemyTV_slot(int,int,int,int,std::string)));
            connect(xe,SIGNAL(dead()),tvXEnemy.get(),SLOT(dead_slot()));
        }
        else
        {//if normal enemy
            auto tvEnemy = std::make_shared<EnemyTextView>(e->getXPos(),e->getYPos());
            tvEnemies.push_back(tvEnemy);
            //connect normal enemy textview
            connect(e.get(),SIGNAL(dead()),tvEnemy.get(),SLOT(dead_slot()));
        }
    }

    //create HP textview and connect
    for(auto &hp: model->myHP){
        auto tvHP = std::make_shared<HealthPackTextView>(hp->getXPos(),hp->getYPos());
        tvHealthPacks.push_back(tvHP);
        connect(hp.get(),SIGNAL(used_signal()),tvHP.get(),SLOT(used_slot()));
    }

    //create environment textview
    for (int row=0; row < rows; row++) {
        for(int col = 0; col < cols; col++){
            int xPos = model->myEnvironment.at(col+row*cols)->getXPos();
            int yPos = model->myEnvironment.at(col+row*cols)->getYPos();
            float val = model->myEnvironment.at(col+row*cols)->getValue();
            auto tvEnvi = std::make_shared<EnvironmentTextView>(xPos, yPos, val);
            tvEnvironments.push_back(tvEnvi);
            tiles.push_back(tvEnvi->getEnvironment());//either "." or "+"
        }
    }
    initTextView();
}


void TextView::initTextView()
{
    //draw protag
    int idx = tvProtag->getYPos()*cols+tvProtag->getXPos();
    tiles.at(idx) = tvProtag->getProtag();//"P "
    //draw normal enemies
    for (auto &tvEnemy:tvEnemies)
    {
        idx = tvEnemy->getYPos()*cols+tvEnemy->getXPos();
        tiles.at(idx) = tvEnemy->getEnemy();//"E "
    }
    //draw penemies
    for (auto &tvPEnemy:tvPEnemies)
    {
        idx = tvPEnemy->getYPos()*cols+tvPEnemy->getXPos();
        tiles.at(idx) = tvPEnemy->getPEnemy();//"P"
    }
    //draw xenemies
    for(auto &tvXEnemy: tvXEnemies)
    {
        idx = tvXEnemy->getYPos()*cols+tvXEnemy->getXPos();
        tiles.at(idx) =tvXEnemy->getXEnemy();//"X"
    }
    //draw healthpacks
    for(auto &tvHP: tvHealthPacks)
    {
        idx = tvHP->getYPos()*cols+tvHP->getXPos();
        tiles.at(idx) = tvHP->getHealthPack();
    }

    //visualize all textviews
    draw();
}

void TextView::draw()
{
    std::cout<<"Energy remains: "<<model->myProtagonist->getEnergy()<<
               "  Health remains: "<<model->myProtagonist->getHealth()<<std::endl;
    for(int r=0;r<rows;r++)
    {
        for(int c=0;c<cols;c++)
        {
            std::cout<<tiles.at(r*cols+c);
        }
        std::cout<<std::endl;
    }
}

void TextView::updateProtagPosition(int x, int y)
{
    //clear previous
    int oldX = tvProtag->getXPos();
    int oldY = tvProtag->getYPos();
    //use different visualization for defeated enemies
    //if neither normal enemies nor penemies, set to " "
    tiles.at(oldY*cols+oldX) = tvEnvironments.at(oldY*cols+oldX)->getEnvironment();
    //if old place is normal enemies, set to "@"
    for(auto &tvEnemy : tvEnemies){
        if(tvEnemy->getXPos()==oldX && tvEnemy->getYPos()==oldY)
           tiles.at(oldY*cols+oldX) =  tvEnemy->getEnemy();//"@"
    }
    //if old place is penemies, set to "&"
    for(auto &tvPEnemy : tvPEnemies){
        if(tvPEnemy->getXPos()==oldX && tvPEnemy->getYPos()==oldY)
           tiles.at(oldY*cols+oldX) =  tvPEnemy->getPEnemy();//defeated textview "&"
    }
    //if old place is xenemies, set to "$"
    for(auto &tvXEnemy : tvXEnemies){
        if(tvXEnemy->getXPos()==oldX && tvXEnemy->getYPos()==oldY)
           tiles.at(oldY*cols+oldX) =  tvXEnemy->getXEnemy();//defeated textview "&"
    }

    //update textview position
    tvProtag->updatePosition(x,y);
    tiles.at(y*cols+x) = tvProtag->getProtag();//"P"
    redraw();
}

void TextView::updateXEnemyTV_slot(int oldX, int oldY, int newX, int newY, std::string xenemy)
{
    tiles.at(oldY*cols+oldX) = tvEnvironments.at(oldY*cols+oldX)->getEnvironment();//"."
    //draw new xenemy
    tiles.at(newY*cols+newX) = xenemy;//"X"
    redraw();
}

void TextView::redraw()
{
    std::cout<<"Energy remains: "<<model->myProtagonist->getEnergy()<<
               "  Health remains: "<<model->myProtagonist->getHealth()<<std::endl;
    int px = tvProtag->getXPos();//updated position
    int py = tvProtag->getYPos();//updated position
    std::cout<<"protagonist at position ("<<px<<", "<<py<<")"<<std::endl;
    QString str = "";
    for(int r=py-4;r<=py+4;r++)
    {
        for(int c=px-15;c<=px+15;c++)
        {
            //display the world within the boundary
            if(r>=0 && r<=model->myWorld->getRows()-1 && c>=0 && c<=model->myWorld->getCols()-1){
                str.append(QString::fromStdString(tiles.at(r*cols+c)));
                std::cout<<tiles.at(r*cols+c);
            }
        }
        str.append(QString::fromStdString("\n"));
        std::cout<<std::endl;
    }
    emit redraw_textbrowser(str);
}

