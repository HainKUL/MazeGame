#include "controller.h"
#include "xenemy.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QDialog>
#include <QMessageBox>


bool proMoving;

Controller::Controller(QString fname, unsigned int nrEnemies, unsigned int nrHPs): QObject ()
{
    createModel(fname, nrEnemies, nrHPs);
    proMoving = false;
    connect(this,SIGNAL(pathGet()),this->myModel.get(),SLOT(pathGet_slot()));
}

void Controller::createModel(QString fname, unsigned int nrEnemies, unsigned int nrHPs){
    myModel = std::make_shared<Model>(fname, nrEnemies, nrHPs);
    COL = myModel->myWorld->getCols();
    ROW = myModel->myWorld->getRows();
    bindPEnemy();
    xEnemyMovingEnemy();
}

void Controller::ProtagonistMove_slot(DIRECTION d){
    if(pause){
        return;
    }
    int tempX = myModel->myProtagonist->getXPos();
    int tempY = myModel->myProtagonist->getYPos();
    if(!proMoving){
        switch(d){
        case UP:{
            if(checkDes(tempX, tempY, tempX,tempY-1)!=0){
                myModel->myProtagonist->setYPos(tempY-1);
            }
            break;
        }
        case DOWN:{
            if(checkDes(tempX, tempY, tempX,tempY+1)!=0){
                myModel->myProtagonist->setYPos(tempY+1);
            }
            break;
        }
        case LEFT:{
            if(checkDes(tempX, tempY, tempX-1,tempY)!=0){
                myModel->myProtagonist->setXPos(tempX-1);
            }
            break;
        }
        case RIGHT:{
            if(checkDes(tempX, tempY, tempX+1,tempY)!=0){
                myModel->myProtagonist->setXPos(tempX+1);
            }
            break;
        }
        case NOCHANGE:{
            break;
        }
        }
    }
}

void Controller::PosionedTile_model_slot(int poisonLevel)
{
    if(poison_state==1){
        changeTileValue(1,poisonLevel);
        if(poisonLevel>=10.0f){
            poison_state = 2;
        }
        return;
    }
    if(poison_state==2&&poisonLevel>=25.0f){
        changeTileValue(2,poisonLevel);
        poison_state = 3;
    }else if(poison_state==3&&poisonLevel<20.0f){
        changeTileValue(3,poisonLevel);
        poison_state = 1;
    }
}

void Controller::changeTileValue(int layer, int poison)
{
    auto &pene = myModel->myEnemies.at(current_enemy);
    int x = pene->getXPos();
    int y = pene->getYPos();

    switch (layer) {
    case 1:{
        myModel->myEnvironment.at(y*COL+x)->setVPoisonValue(poison);
        break;
    }
    case 2:{
        changeTileValue(1,poison);
        //at 5
        if(x>0&&x+1<COL&&y>0&&y+1<ROW){
            checkTileValue(x-1,y-1,poison);
            checkTileValue(x-1,y,poison);
            checkTileValue(x-1,y+1,poison);
            checkTileValue(x,y-1,poison);
            checkTileValue(x,y+1,poison);
            checkTileValue(x+1,y-1,poison);
            checkTileValue(x+1,y,poison);
            checkTileValue(x+1,y+1,poison);
            break;
        }
        else if(x==0&&x+1<COL){
            //at 4
            if(y>0&&y+1<ROW){
                checkTileValue(x,y-1,poison);
                checkTileValue(x,y+1,poison);
                checkTileValue(x+1,y-1,poison);
                checkTileValue(x+1,y,poison);
                checkTileValue(x+1,y+1,poison);
                break;
            }
            //at7
            else if(y==0&&y+1<ROW){
                checkTileValue(x,y+1,poison);
                checkTileValue(x+1,y,poison);
                checkTileValue(x+1,y+1,poison);
                break;
            }
            //at1
            else if(y>0&&y+1==ROW){
                checkTileValue(x,y-1,poison);
                checkTileValue(x+1,y-1,poison);
                checkTileValue(x+1,y,poison);
                break;
            }
        }
        else if(y==0&&y+1<ROW){
            //at 8
            if(x>0&&x+1<COL){
                checkTileValue(x-1,y,poison);
                checkTileValue(x-1,y+1,poison);
                checkTileValue(x,y+1,poison);
                checkTileValue(x+1,y,poison);
                checkTileValue(x+1,y+1,poison);
                break;
            }
            //at 9
            else if(x>0&&x==COL){
                checkTileValue(x-1,y,poison);
                checkTileValue(x-1,y+1,poison);
                checkTileValue(x,y+1,poison);
                break;
            }
        }
        else if(x>0&&x==COL){
            //at 6
            if(y>0&&y+1<ROW){
                checkTileValue(x,y-1,poison);
                checkTileValue(x,y+1,poison);
                checkTileValue(x-1,y-1,poison);
                checkTileValue(x-1,y,poison);
                checkTileValue(x-1,y+1,poison);
                break;
            }
            //at 3
            else if(y>0&&y==ROW){
                checkTileValue(x,y-1,poison);
                checkTileValue(x-1,y-1,poison);
                checkTileValue(x-1,y,poison);
                break;
            }
        }
        else if(y>0&&y==ROW){
            //at 2
            if(x>0&&x+1<COL){
                checkTileValue(x-1,y,poison);
                checkTileValue(x-1,y-1,poison);
                checkTileValue(x,y+1,poison);
                checkTileValue(x+1,y,poison);
                checkTileValue(x+1,y-1,poison);
                break;
            }
        }
        break;
    }
    case 3:{
        changeTileValue(2,poison);
        //at center
        if(x>1&&x+2<COL&&y>1&&y+2<ROW){
            checkTileValue(x-2,y-2,poison);
            checkTileValue(x-2,y-1,poison);
            checkTileValue(x-2,y,poison);
            checkTileValue(x-2,y+1,poison);
            checkTileValue(x-2,y+2,poison);

            checkTileValue(x-1,y-2,poison);
            checkTileValue(x-1,y+2,poison);

            checkTileValue(x,y-2,poison);
            checkTileValue(x,y+2,poison);

            checkTileValue(x+1,y-2,poison);
            checkTileValue(x+1,y+2,poison);

            checkTileValue(x+2,y-2,poison);
            checkTileValue(x+2,y-1,poison);
            checkTileValue(x+2,y,poison);
            checkTileValue(x+2,y+1,poison);
            checkTileValue(x+2,y+2,poison);
            break;
        }

        else if(x==1&&x+2<COL){
            //at 4
            if(y>0&&y+1<ROW){
                checkTileValue(x-1,y-2,poison);
                checkTileValue(x-1,y+2,poison);

                checkTileValue(x,y-2,poison);
                checkTileValue(x,y+2,poison);

                checkTileValue(x+1,y-2,poison);
                checkTileValue(x+1,y+2,poison);

                checkTileValue(x+2,y-2,poison);
                checkTileValue(x+2,y-1,poison);
                checkTileValue(x+2,y,poison);
                checkTileValue(x+2,y+1,poison);
                checkTileValue(x+2,y+2,poison);
                break;
            }
            //at7
            else if(y==1&&y+1<ROW){
                checkTileValue(x-1,y+2,poison);

                checkTileValue(x,y+2,poison);

                checkTileValue(x+1,y+2,poison);

                checkTileValue(x+2,y-1,poison);
                checkTileValue(x+2,y,poison);
                checkTileValue(x+2,y+1,poison);
                checkTileValue(x+2,y+2,poison);
                break;
            }
            //at1
            else if(y>1&&y+1==ROW){
                checkTileValue(x-1,y-2,poison);

                checkTileValue(x,y-2,poison);

                checkTileValue(x+1,y-2,poison);

                checkTileValue(x+2,y-2,poison);
                checkTileValue(x+2,y-1,poison);
                checkTileValue(x+2,y,poison);
                checkTileValue(x+2,y+1,poison);
                break;
            }
        }
        else if(y==1&&y+2<ROW){
            //at 8
            if(x>1&&x+2<COL){
                checkTileValue(x-2,y-1,poison);
                checkTileValue(x-2,y,poison);
                checkTileValue(x-2,y+1,poison);
                checkTileValue(x-2,y+2,poison);

                checkTileValue(x-1,y+2,poison);

                checkTileValue(x,y+2,poison);

                checkTileValue(x+1,y+2,poison);

                checkTileValue(x+2,y-1,poison);
                checkTileValue(x+2,y,poison);
                checkTileValue(x+2,y+1,poison);
                checkTileValue(x+2,y+2,poison);
                break;
            }
            //at 9
            else if(x>1&&x+1==COL){
                checkTileValue(x-2,y-1,poison);
                checkTileValue(x-2,y,poison);
                checkTileValue(x-2,y+1,poison);
                checkTileValue(x-2,y+2,poison);

                checkTileValue(x-1,y+2,poison);

                checkTileValue(x,y+2,poison);

                checkTileValue(x+1,y+2,poison);
                break;
            }
        }
        else if(x>1&&x+1==COL){
            //at 6
            if(y>1&&y+2<ROW){
                checkTileValue(x-2,y-2,poison);
                checkTileValue(x-2,y-1,poison);
                checkTileValue(x-2,y,poison);
                checkTileValue(x-2,y+1,poison);
                checkTileValue(x-2,y+2,poison);

                checkTileValue(x-1,y-2,poison);
                checkTileValue(x-1,y+2,poison);

                checkTileValue(x,y-2,poison);
                checkTileValue(x,y+2,poison);

                checkTileValue(x+1,y-2,poison);
                checkTileValue(x+1,y+2,poison);
                break;
            }
            //at 3
            else if(y>1&&y+1==ROW){
                checkTileValue(x-2,y-2,poison);
                checkTileValue(x-2,y-1,poison);
                checkTileValue(x-2,y,poison);
                checkTileValue(x-2,y+1,poison);

                checkTileValue(x-1,y-2,poison);

                checkTileValue(x,y-2,poison);

                checkTileValue(x+1,y-2,poison);
                break;
            }
        }
        else if(y>1&&y+1==ROW){
            //at 2
            if(x>1&&x+2<COL){
                checkTileValue(x-2,y-2,poison);
                checkTileValue(x-2,y-1,poison);
                checkTileValue(x-2,y,poison);
                checkTileValue(x-2,y+1,poison);

                checkTileValue(x-1,y-2,poison);

                checkTileValue(x,y-2,poison);

                checkTileValue(x+1,y-2,poison);

                checkTileValue(x+2,y-2,poison);
                checkTileValue(x+2,y-1,poison);
                checkTileValue(x+2,y,poison);
                checkTileValue(x+2,y+1,poison);
                break;
            }
        }
        break;
    }
    default: break;
    }
}

void Controller::checkTileValue(int x, int y, int poison)
{
    if(myModel->myEnvironment.at(y*COL+x)->getValue()!=std::numeric_limits<float>::infinity())
        myModel->myEnvironment.at(y*COL+x)->setVPoisonValue(poison);
}

void Controller::bindPEnemy()
{
    for(auto &e:myModel->myEnemies){
        auto pe = dynamic_cast<PEnemy *>(e.get());
        if(pe)
        {//penemy
            connect(pe,SIGNAL(poisonLevelUpdated(int)),this,SLOT(PosionedTile_model_slot(int)));
        }
    }
}

int Controller::ifSolid(int posX, int posY)
{
    if(posX<0||posX>ROW||posY<0||posY>COL){
        return 0;
    }
    else if(myModel->myEnvironment.at(posY*COL+posX)->getValue() == std::numeric_limits<float>::infinity()){
        return 0;
    } else {
        for(auto &p:myModel->myEnemies){
            if(p->getXPos()==posX&&p->getYPos()==posY) return 2;
        }
        for(auto &p:myModel->myHP){
            if(p->getXPos()==posX&&p->getYPos()==posY) return 2;
        }
        return 1;
    }

}

int Controller::checkDes(int tempX,int tempY, int posX, int posY)
{
    if(ifSolid(posX,posY)){

        //check energy and health
        float finalEnergy = checkEnergyHealth(tempX,tempY,posX,posY);
        if(finalEnergy<0.0f){
            // dead because of poison;
            // cannot go
            emit loose();
            return 0;
        }

        //check type
        for(int i =0;i<myModel->myEnemies.size();i++){
            if(myModel->myEnemies.at(i)->getXPos()==posX&&myModel->myEnemies.at(i)->getYPos()==posY){
                if(!myModel->myEnemies.at(i)->getDefeated()){
                    sendMessage("You meet Enemy\n");
                    if(fight){
                        //fight
                        current_enemy = i;
                        myModel->myProtagonist->setEnergy(finalEnergy);
                        return meetEnemy();
                    }
                    else{
                        // dont fight
                        return 8;
                    }
                }
                else return 0;
            }
        }
        for(int i =0;i<myModel->myHP.size();i++){
            if(myModel->myHP.at(i)->getXPos()==posX&&myModel->myHP.at(i)->getYPos()==posY){
                sendMessage("You meet a Health Pack\n");
                meetHP(i);
                myModel->myProtagonist->setEnergy(finalEnergy);
                return 2;
            }
        }
        myModel->myProtagonist->setEnergy(finalEnergy);
        return 3;
    }
   return 0;
    // TO DO: check if enermies or health pack
}

int Controller::meetEnemy()
{
    float health = myModel->myProtagonist->getHealth();
    float damage = myModel->myEnemies.at(current_enemy)->getValue()/scale_diff;
    //win
    if(damage<=health){
        qDebug()<<"win";
        //set defeated enemy's value to infinity for pathfinder
        int xpos=myModel->myEnemies.at(current_enemy)->getXPos();
        int ypos=myModel->myEnemies.at(current_enemy)->getYPos();
        myModel->getPathfinder()->setInf(xpos+ypos*COL);
        if(dynamic_cast<PEnemy *>(myModel->myEnemies.at(current_enemy).get()))
        {//penemy
            myModel->myProtagonist->setHealth(health-damage);
            myModel->myEnemies.at(current_enemy)->setDefeated(true);
            myModel->myProtagonist->setEnergy(100);
            dynamic_cast<PEnemy *>(myModel->myEnemies.at(current_enemy).get())->poison();
            qDebug()<<"remaining enemies: "<<NrAliveEnemies();
            if(NrAliveEnemies()==0)
                emit win();
            return 5;
        }
        else
        {//normal enemy or xenemiy
            myModel->myProtagonist->setHealth(health-damage);
            myModel->myEnemies.at(current_enemy)->setDefeated(true);
            myModel->myProtagonist->setEnergy(100);
            qDebug()<<"remaining enemies: "<<NrAliveEnemies();
            if(NrAliveEnemies()==0)
                emit win();
            return 1;
        }


    }
    //loose
    else {
        sendMessage("You are defeated\n");
        myModel->myProtagonist->setHealth(health-damage);
        emit loose();
        return 4;
    }
}

void Controller::meetHP(int id)
{
    float health = myModel->myProtagonist->getHealth();
    float target = health+myModel->myHP.at(id)->getValue();
    if(target>100) target=100;
    myModel->myProtagonist->setHealth(target);
    myModel->myHP.at(id)->setUsed(true);
    myModel->myHP.erase(myModel->myHP.begin()+id);
}

float Controller::checkEnergyHealth(int tempX, int tempY,int posX, int posY)
{
    float res = scale_diff*(myModel->myEnvironment.at(tempY*COL+tempX)->getValue() - myModel->myEnvironment.at(posY*COL+posX)->getValue());
    res = myModel->myProtagonist->getEnergy()-abs(res);
    if(myModel->myEnvironment.at(posY*COL+posX)->getPoison()!=0.0f){
        myModel->myProtagonist->setHealth(myModel->myProtagonist->getHealth()-
                                          myModel->myEnvironment.at(posY*COL+posX)->getPoison()/10);
    }
    if(res<0||myModel->myProtagonist->getHealth()<=0.0f){
        sendMessage("You died!\n");
        emit loose();
        return -1.0f;
    }
    return res;
}


// check the number of remaining live enemies
int Controller:: NrAliveEnemies()
{
    int aliveEnemy=0;
    for(auto & enemy:myModel->myEnemies)
    {
        if(enemy->getDefeated()==false)aliveEnemy++;
    }
    return aliveEnemy;
}


//trigger the auto play mode
void Controller::autoPlay_slot()
{
    qDebug()<<"receive autoPlay signal";
    strategy();
}

//the auto play strategy
int Controller::strategy()
{
    // condition for auto play mode
   while(NrAliveEnemies()>0&&myModel->myProtagonist->getHealth()>0&&myModel->myProtagonist->getEnergy()>0&&autoPlay)
   {
       //qDebug()<<" alive enemies";
       float enemyHealth=myModel->getNearestEnemy()->getValue()/scale_diff;
       qDebug()<<"the poision of nearest enemy is"<<enemyHealth<<"x: " <<myModel->getNearestEnemy()->getXPos()<< myModel->getNearestEnemy()->getYPos();
       float proHP=myModel->myProtagonist->getHealth();
       //qDebug()<<"the health of Protagonist :" <<proHP;
       GridLocation grid=GridLocation{0,0,myModel->myProtagonist->getXPos(),myModel->myProtagonist->getYPos(),0,0,0};
       myModel->getPathfinder()->setMystart(grid);
       //qDebug()<<"the position of Protagonist :" <<myModel->myProtagonist->getXPos()<< " "<<myModel->myProtagonist->getYPos();
       // Health is not enough and there  are still healthpack(HP) available
       // Go get the nearest HP
       if(enemyHealth>=proHP&&myModel->myHP.size()>0)
       {//pick hp
           qDebug()<<" go get health pack";
           int result= goToDes(myModel->getNearestHP()->getXPos(),myModel->getNearestHP()->getYPos());
           if(result==1)//  protag died
           {
               qDebug()<<"Game Over!";
               return 1;
           }
       }

       //health is enoughto beat  nearest enemy
      else if(enemyHealth<proHP)
       {//defeat enemy
          qDebug()<<" beat enemy";
          int result =goToDes(myModel->getNearestEnemy()->getXPos(),myModel->getNearestEnemy()->getYPos());

          if(result==1)//  protag died
          {
              qDebug()<<"Game Over! died";
              return 1;
          }
       }

       // not enough health plus no HP available
       else/*(myModel->myHP.size()==0)*/
       {
          qDebug()<< "failed, no more healthpack and insufficient energy";
          int result =goToDes(myModel->getNearestEnemy()->getXPos(),myModel->getNearestEnemy()->getYPos());

          if(result==1)//  protag died
          {
              return 1;
          }

            return 0;
       }
   }

   if(myModel->myEnemies.size()==0) return 1;
   else return 0;
}


// go to the point (x,y)
int Controller::goToDes(int x,int y)
{
    //fight=false;
    GridLocation grid=GridLocation{0,0,myModel->myProtagonist->getXPos(),myModel->myProtagonist->getYPos(),0,0};
    myModel->getPathfinder()->setMystart(grid);
    bool isXenemy=false;
    XEnemy *current=nullptr;
    if(myModel->getNearestEnemy()->getXPos()==x&&myModel->getNearestEnemy()->getYPos()==y)
    {
          auto xe = dynamic_cast<XEnemy *>(myModel->getNearestEnemy());
          if(xe)
          {//xenemy
              current = xe;//raw ptr pointing to xenemy
              isXenemy = true;
          }
    }

    GridLocation goal=GridLocation{0,0,x,y,0,0,0};
    myModel->getPathfinder()->setGoal(goal);
    qDebug()<<"go to position:"<<x <<" , "<<y ;
    if(myModel->getPathfinder()->find()==true)
    {
        myModel->getPathfinder()->generatePath();
        auto path=myModel->getPathfinder()->getPath();

        //energy is not enough to complete the whole path
        //go collect the nearest HP
        if(getMaxCost()>myModel->myProtagonist->getEnergy()-1)
        {
            return goToDes(myModel->getNearestHP()->getXPos(),myModel->getNearestHP()->getYPos());
        }
        else
        {

            emit pathGet();// signal the draw the path on the scene
            for(int i=0;i<path.size();i++)
            {
                if(autoPlay){
                    auto temp=path[i];
                    int result=checkDes(myModel->myProtagonist->getXPos(),myModel->myProtagonist->getYPos(),temp.x,temp.y);
                    //qDebug()<<"result:"<<result;
                    if(result==4)
                    {
                        return 1;//meet powerful enemy-->protag died
                    }


                    else if(result==8)// meet enemy re-route
                    {
                        float value=myModel->getPathfinder()->getMap()[temp.x+temp.y*COL].value;
                        myModel->getPathfinder()->setInf(temp.x+temp.y*COL);
                        int  ret=goToDes(x,y);
                        myModel->getPathfinder()->setValue(temp.x+temp.y*COL,value);
                        return ret;
                    }

                    else{
                        //one step before the destination
                        //enable fight -->beat the enemy
                        if(i==path.size()-2)
                        {
                            fight=true;
                            //qDebug()<<" index"<<i<<" pathsize:"<<path.size();
                        }
                        //emit posChanged(int,int) -->signal to update the view
                        myModel->myProtagonist->setPos(temp.x,temp.y);

                        //delay 500 mSec for each step;
                        QTime _Timer = QTime::currentTime().addMSecs(static_cast<int>(300*scale));
                        while( QTime::currentTime() < _Timer )
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                        //special usage for XEnemy--> to deal with the moving position of XEnemy
                        //move to the middle of previous path--> search the path again
                        if(i>path.size()/2&&isXenemy==true)
                        {
                           return goToDes(current->getXPos(),current->getYPos());
                        }
                    }

                }

            }
        }

    }
    return 0;
}


//check if the max energy consumption during path
float Controller::getMaxCost()
{
    float maxCost=0;
    auto path=myModel->getPathfinder()->getPath();
    if(path.size()>1)
    {
        for(int i=1;i<path.size();i++)
        {
            if(path[i].value-path[0].value>maxCost)
                maxCost=path[i].value-path[0].value;
        }
    }
    return maxCost;
}

float Controller::getScale() const
{
    return scale;
}

void Controller::setScale(float value)
{
    scale = value;
}

// go to the position where the nouse is clicked
void Controller::goClickedPos(int x, int y)
{
    autoPlay=true;
    goToDes(x,y);
    autoPlay=false;
}

bool Controller::getPause() const
{
    return pause;
}

void Controller::setPause(bool value)
{
    pause = value;
}

bool Controller::getAutoPlay() const
{
    return autoPlay;
}

void Controller::setAutoPlay(bool value)
{
    //    qDebug()<<value;
    autoPlay = value;
}

void Controller::xEnemyMovingEnemy()
{
    if(pause){
        return;
    }
    unsigned int temp = static_cast<unsigned int>(myModel->getNrOfEnemies()*0.2);
    for(auto &e:myModel->myEnemies){
        auto xe = dynamic_cast<XEnemy *>(e.get());
        //std::unique_ptr<XEnemy> xe(dynamic_cast<XEnemy *>(e.get()));
        if(xe)
        {//xenemy
            if(temp!=0){
                if(xe->getDefeated()){
                    temp--;
                    continue;
                }
                //&&temp!=0
                int tempX = xe->getXPos();
                int tempY = xe->getYPos();
                DIRECTION d = DIRECTION(qrand()%4);
                switch (d){
                case UP:{
                    if(ifSolid(tempX,tempY-1)==1){
                        xe->setPosition(tempX,tempY-1);//it will emit positionChanged signal of xenemy
                    }
                    break;
                }
                case DOWN:{
                    if(ifSolid(tempX,tempY+1)==1){
                        xe->setPosition(tempX,tempY+1);
                    }
                    break;
                }
                case LEFT:{
                    if(ifSolid(tempX-1,tempY)==1){
                        xe->setPosition(tempX-1,tempY);
                    }
                    break;
                }
                case RIGHT:{
                    if(ifSolid(tempX+1,tempY)==1){
                        xe->setPosition(tempX+1,tempY);
                    }
                    break;
                }
                default: break;
                }
                //qDebug()<<xe->getXPos()<<xe->getYPos();
                temp--;
            }
            else break;
        }
        else {
            continue;
        }
    }
    QTimer::singleShot(2231, this, SLOT(xEnemyMovingEnemy()));
}
