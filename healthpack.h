#ifndef HEALTHPACK_H
#define HEALTHPACK_H
#include "world.h"

class HealthPack: public QObject, public Tile
{
    Q_OBJECT
public:
    HealthPack(int xPosition, int yPosition, float tileWeight);
    virtual ~HealthPack() = default;
    void setUsed(bool value);

signals:
    void used_signal();

private:
    bool used;
};

#endif // HEALTHPACK_H
