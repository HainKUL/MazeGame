#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include <QGraphicsPixmapItem>
#include <QObject>


class EnemyView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyView();
    virtual ~EnemyView();

public slots:
    void updates();
    void updatesDeath();
    void dead_slot();

private:
    int nrOfPic = 4;
    QTimer *timer;
    QTimer *timerDeath;

};

#endif // ENEMYVIEW_H
