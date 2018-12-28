#include "penemyview.h"
#include <QTimer>

PEnemyView::PEnemyView()
{
    setPixmap(QPixmap(":/images/P_1.png").scaled(50,50,Qt::KeepAspectRatio));
    nrOfPic = 4;
    timer = new QTimer();
    timerDeath = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updates()));
    connect(timerDeath, SIGNAL(timeout()), this, SLOT(updatesDeath()));
    timer->start(120);
}

PEnemyView::~PEnemyView()
{
    delete timerDeath;
    delete timer;
}

void PEnemyView::updates()
{
    switch (nrOfPic) {
    case 1:{
        setPixmap(QPixmap(":/images/P_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic=4;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/P_4.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/P_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 4:{
        setPixmap(QPixmap(":/images/P_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    }
}

void PEnemyView::updatesDeath()
{
    switch (nrOfPic) {
    case 1:{
        setPixmap(QPixmap(":/images/P_DEATH_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic=3;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/P_DEATH_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/P_DEATH_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    }
}

void PEnemyView::dead_slot()
{
    timer->stop();
    nrOfPic = 3;
    timerDeath->start(120);
}
