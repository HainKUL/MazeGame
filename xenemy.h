#ifndef XENEMY_H
#define XENEMY_H
#include <world.h>
#include <config.h>

class XEnemy: public Enemy
{
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);
    virtual ~XEnemy() = default;
    void setPosition(int x, int y);

signals:
    void positionChanged(int x, int y, DIRECTION d);

public slots:
};

#endif // XENEMY_H
