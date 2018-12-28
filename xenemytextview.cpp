#include "xenemytextview.h"
#include <iostream>

XEnemyTextView::XEnemyTextView(int xPosition, int yPosition):
    xPos{xPosition},yPos{yPosition}
{
    xenemy = "X";
}

XEnemyTextView::~XEnemyTextView()
{

}

int XEnemyTextView::getXPos() const
{
    return xPos;
}

int XEnemyTextView::getYPos() const
{
    return yPos;
}

void XEnemyTextView::dead_slot()
{
    xenemy = "$";//defeated visualization for xenemies
}

std::string XEnemyTextView::getXEnemy() const
{
    return xenemy;
}

void XEnemyTextView::updateXEnemyPosition(int x, int y)
{
    int oldX = this->getXPos();
    int oldY = this->getYPos();
    xPos = x;
    yPos = y;
    emit updateXEnemyTV_signal(oldX,oldY,xPos,yPos,xenemy);//send old/new position about the xenemy and the visualization
}
