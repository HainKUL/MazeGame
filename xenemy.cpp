#include "xenemy.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength): Enemy(xPosition, yPosition, strength)
{

}

void XEnemy::setPosition(int x, int y)
{
    DIRECTION d;
    if(x>this->getXPos()){
        d = RIGHT;
    }else if(x<this->getXPos()){
        d = LEFT;
    }else if (y>this->getYPos()) {
        d = DOWN;
    }else if(y<this->getYPos()){
        d = UP;
    }else {
        d = NOCHANGE;
    }
    this->setXPos(x);
    this->setYPos(y);
    emit positionChanged(x,y,d);
}

