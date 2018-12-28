#include "xenemyview.h"
#include <QThread>
#include <QTimer>
#include <iostream>
#include <controller.h>

XEnemyView::XEnemyView()
{
    setPixmap(QPixmap(":/images/X_DOWN_1.png").scaled(50,50,Qt::KeepAspectRatio));
    timerR = new QTimer();
    timerL = new QTimer();
    timerU = new QTimer();
    timerD = new QTimer();
    timerDeath = new QTimer();
    connect(timerR, SIGNAL(timeout()), this, SLOT(updatesRight()));
    connect(timerL, SIGNAL(timeout()), this, SLOT(updatesLeft()));
    connect(timerU, SIGNAL(timeout()), this, SLOT(updatesUp()));
    connect(timerD, SIGNAL(timeout()), this, SLOT(updatesDown()));
    connect(timerDeath, SIGNAL(timeout()), this, SLOT(updatesDeath()));
}

XEnemyView::~XEnemyView()
{
    delete timerR;
    delete timerL;
    delete timerU;
    delete timerD;
    delete timerDeath;

}

float XEnemyView::getScale() const
{
    return scale;
}

void XEnemyView::setScale(float value)
{
    scale = value;
}


void XEnemyView::move(int x, int y, DIRECTION d)
{
    targetX = x;
    targetY = y;
    
    switch(d){
    case RIGHT:{
        proMoving = true;
            timerR->start(static_cast<int>(30*scale));
            break;
        }
        case LEFT:{
        proMoving = true;
            timerL->start(static_cast<int>(30*scale));
            break;
        }
        case UP:{
        proMoving = true;
            timerU->start(static_cast<int>(30*scale));
            break;
        }
        case DOWN:{
        proMoving = true;
            timerD->start(static_cast<int>(30*scale));
            break;
        }
        case NOCHANGE:{
            break;
        }
    }
}

void XEnemyView::updatesRight()
{
    switch (nrOfMove%4) {
    case 0:{
        setPixmap(QPixmap(":/images/X_RIGHT_1.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX-1)+step*4+4*turn*step);
        if(turn){
            nrOfMove=7;
            turn = 0;
            timerR->stop();
            proMoving = false;
            break;

        }
        nrOfMove-=1;
        turn=1;
        break;
    }
    case 1:{
        setPixmap(QPixmap(":/images/X_RIGHT_4.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX-1)+step*3+4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/X_RIGHT_3.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX-1)+step*2+4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/X_RIGHT_2.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX-1)+step+4*turn*step);
        nrOfMove-=1;
        break;
    }
    }
}

void XEnemyView::updatesLeft()
{
    switch (nrOfMove%4) {
    case 0:{
        setPixmap(QPixmap(":/images/X_LEFT_1.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX+1)-step*4-4*turn*step);
        if(turn){
            nrOfMove=7;
            turn = 0;
            timerL->stop();
            proMoving = false;
            break;
        }
        nrOfMove-=1;
        turn=1;
        break;
    }
    case 1:{
        setPixmap(QPixmap(":/images/X_LEFT_4.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX+1)-step*3-4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/X_LEFT_3.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX+1)-step*2-4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/X_LEFT_2.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setX(50*(targetX+1)-step-4*turn*step);
        nrOfMove-=1;
        break;
    }
    }
}

void XEnemyView::updatesUp()
{
    switch (nrOfMove%4) {
    case 0:{
        setPixmap(QPixmap(":/images/X_UP_1.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY+1)-step*4-4*turn*step);
        if(turn){
            nrOfMove=7;
            turn = 0;
            timerU->stop();
            proMoving = false;
            break;
        }
        turn=1;
        nrOfMove-=1;
        break;
    }
    case 1:{
        setPixmap(QPixmap(":/images/X_UP_4.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY+1)-step*3-4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/X_UP_3.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY+1)-step*2-4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/X_UP_2.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY+1)-step-4*turn*step);
        nrOfMove-=1;
        break;
    }
    }
}

void XEnemyView::updatesDown()
{
    switch (nrOfMove%4) {
    case 0:{
        setPixmap(QPixmap(":/images/X_DOWN_1.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY-1)+step*4+4*turn*step);
        if(turn){
            nrOfMove=7;
            turn = 0;
            timerD->stop();
            proMoving = false;
            break;
        }
        nrOfMove-=1;
        turn=1;
        break;
    }
    case 1:{
        setPixmap(QPixmap(":/images/X_DOWN_4.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY-1)+step*3+4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/X_DOWN_3.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY-1)+step*2+4*turn*step);
        nrOfMove-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/X_DOWN_2.png").scaled(50,50,Qt::KeepAspectRatio));
        this->setY(50*(targetY-1)+step+4*turn*step);
        nrOfMove-=1;
        break;
    }
    }
}

void XEnemyView::updatesDeath()
{
    switch (nrOfMove) {
    case 1:{
        setPixmap(QPixmap(":/images/X_DEATH_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfMove=3;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/X_DEATH_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfMove-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/X_DEATH_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfMove-=1;
        break;
    }
    }
}

void XEnemyView::dead_slot()
{
    timerR->stop();
    timerL->stop();
    timerU->stop();
    timerD ->stop();
    nrOfMove = 3;
    timerDeath->start(120);
}
