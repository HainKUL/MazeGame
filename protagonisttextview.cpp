#include "protagonisttextview.h"
#include <iostream>

ProtagonistTextView::ProtagonistTextView(int xPosition, int yPosition): xPos{xPosition}, yPos{yPosition}
{
    protag = "U";
}

ProtagonistTextView::~ProtagonistTextView()
{

}


void ProtagonistTextView::updatePosition(int x, int y)
{
    xPos = x;
    yPos = y;
}

void ProtagonistTextView::updateEnergy(int e)
{
    energy = e;
}

void ProtagonistTextView::updateHealth(int h)
{
    health = h;
}

int ProtagonistTextView::getXPos() const
{
    return xPos;
}

int ProtagonistTextView::getYPos() const
{
    return yPos;
}

std::string ProtagonistTextView::getProtag() const
{
    return protag;
}
