#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H
#include <QGraphicsPixmapItem>
#include <config.h>

class ProtagonistView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ProtagonistView();
    virtual ~ProtagonistView();
    void move(int x, int y, DIRECTION d);

    QTimer *timerR;
    QTimer *timerL;
    QTimer *timerU;
    QTimer *timerD;
    bool flag;
    float getScale() const;
    void setScale(float value);

public slots:
    void updatesRight();
    void updatesLeft();
    void updatesUp();
    void updatesDown();

private:
    int nrOfMove = 7;
    double step = 6.25;
    float scale =1.0f;
    int turn = 0;
    int targetX;
    int targetY;
};

#endif // PROTAGONISTVIEW_H
