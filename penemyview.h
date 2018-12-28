#ifndef PENEMYVIEW_H
#define PENEMYVIEW_H

#include <QGraphicsPixmapItem>
#include <QObject>

class PEnemyView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PEnemyView();
    virtual ~PEnemyView();

public slots:
    virtual void updates();
    virtual void updatesDeath();
    void dead_slot();

private:
    int nrOfPic;
    QTimer *timer;
    QTimer *timerDeath;
};

#endif // PENEMYVIEW_H
