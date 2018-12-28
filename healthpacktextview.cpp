#include "healthpacktextview.h"

HealthPackTextView::HealthPackTextView(int xPosition, int yPosition):
    xPos{xPosition}, yPos{yPosition}
{
    healthPack = "H";
}

std::string HealthPackTextView::getHealthPack() const
{
    return healthPack;
}

void HealthPackTextView::used_slot()
{
    healthPack = ".";
}

int HealthPackTextView::getYPos() const
{
    return yPos;
}

int HealthPackTextView::getXPos() const
{
    return xPos;
}
