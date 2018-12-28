#ifndef TESTER_H
#define TESTER_H
//#include <memory>
//#include <QString>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <ctime>
#include "pathfinder.h"
#include "world.h"

class Tester : public QGraphicsScene
{
    Q_OBJECT
public:
    Tester();
    virtual ~Tester();

    std::shared_ptr<Pathfinder> getPathfinder() const;
    void drawPath();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setPos(int x,int y);

private:
    std::shared_ptr<Pathfinder> pathfinder;
    bool startSet;
    QPixmap pixmap;
    int colWorld;

};

#endif // TESTER_H
