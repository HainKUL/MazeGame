#include "healthpackview.h"

#include <QTimer>

HealthPackView::HealthPackView()
{
    setPixmap(QPixmap(":/images/HP_1.png").scaled(50,50,Qt::KeepAspectRatio));
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updates()));
    timer->start(120);
}

HealthPackView::~HealthPackView()
{
    delete timer;
}

// Animation
void HealthPackView::updates()
{
    switch (nrOfPic) {
    case 1:{
        setPixmap(QPixmap(":/images/HP_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic=4;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/HP_4.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/HP_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 4:{
        setPixmap(QPixmap(":/images/HP_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    }
}

void HealthPackView::used_slot()
{
    this->hide();
}
