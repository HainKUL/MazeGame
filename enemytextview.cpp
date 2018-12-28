#include "enemytextview.h"
#include <iostream>

EnemyTextView::EnemyTextView(int xPosition, int yPosition): xPos{xPosition}, yPos{yPosition}
{
    enemy = "E";
}

EnemyTextView::~EnemyTextView()
{

}

void EnemyTextView::dead_slot()
{
    enemy = "@";//defeated visualization for normal enemies
}

std::string EnemyTextView::getEnemy() const
{
    return enemy;
}

int EnemyTextView::getYPos() const
{
    return yPos;
}

int EnemyTextView::getXPos() const
{
    return xPos;
}

