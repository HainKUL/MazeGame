#include "environment.h"

Environment::Environment(int xPosition, int yPosition, float tileWeight):
    Tile(xPosition,yPosition,tileWeight),poison{0.0f}
{
}

void Environment::setVPoisonValue(float newValue)
{
    poison = newValue;
    emit poiValueChanged();
}

float Environment::getPoison() const
{
    return poison;
}

void Environment::setPoison(float value)
{
    //reduce poison level, otherwise it is too hard to win.
    poison = value/20;
}
