#include "healthpack.h"

HealthPack::HealthPack(int xPosition, int yPosition, float tileWeight):
    Tile(xPosition, yPosition, tileWeight), used{false}
{
}

void HealthPack::setUsed(bool value)
{
    used = value;
    if (used){
        emit used_signal();
    }
}
