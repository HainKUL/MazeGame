#ifndef XENEMYVIEW_H
#define XENEMYVIEW_H

#include <QGraphicsPixmapItem>
#include <config.h>

class XEnemyView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    XEnemyView();
    virtual ~XEnemyView();
    float getScale() const;
    void setScale(float value);

public slots:
    void updatesRight();
    void updatesLeft();
    void updatesUp();
    void updatesDown();
    void updatesDeath();
    void dead_slot();
    void move(int x, int y, DIRECTION d);

private:
    int nrOfMove = 7;
    double step = 6.25;
    int turn = 0;
    float scale =1.0f;
    int targetX;
    int targetY;
    bool flag;
    QTimer *timerR;
    QTimer *timerL;
    QTimer *timerU;
    QTimer *timerD;
    QTimer *timerDeath;
};

#endif // XENEMYVIEW_H
