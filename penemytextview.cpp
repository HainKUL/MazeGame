#include "penemytextview.h"
#include <iostream>

PEnemyTextView::PEnemyTextView(int xPosition, int yPosition): xPos{xPosition}, yPos{yPosition}
{
    penemy = "P";
}

PEnemyTextView::~PEnemyTextView()
{

}


void PEnemyTextView::dead_slot()
{
    penemy = "&";//defeated visualization for penemies
}

std::string PEnemyTextView::getPEnemy() const
{
    return penemy;
}

int PEnemyTextView::getYPos() const
{
    return yPos;
}

int PEnemyTextView::getXPos() const
{
    return xPos;
}
