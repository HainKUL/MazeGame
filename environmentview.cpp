#include "environmentview.h"
EnvironmentView::EnvironmentView(float value)
{
    // random pics
    nr = rand()%5+1;
    if(value==std::numeric_limits<float>::infinity()){
        nr = rand()%3+1;
        url.append("black_").append(QString::number(nr)).append(".png");
        setPixmap(QPixmap(url).scaled(50,50,Qt::KeepAspectRatio));
    }else if(value>=0&&value<0.3){
        url.append("blue_").append(QString::number(nr)).append(".png");
        setPixmap(QPixmap(url).scaled(50,50,Qt::KeepAspectRatio));
    }else if(value>=0.3&&value<0.6){
        url.append("yellow_").append(QString::number(nr)).append(".png");
        setPixmap(QPixmap(url).scaled(50,50,Qt::KeepAspectRatio));
    }else {
        url.append("green_").append(QString::number(nr)).append(".png");
        setPixmap(QPixmap(url).scaled(50,50,Qt::KeepAspectRatio));
    }
}

void EnvironmentView::poisoned()
{
    url = ":/images/";
    nr = rand()%5+1;
    url.append("dark_").append(QString::number(nr)).append(".png");
    setPixmap(QPixmap(url).scaled(50,50,Qt::KeepAspectRatio));
}

