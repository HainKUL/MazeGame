#include "environmenttextview.h"
#include <limits>


EnvironmentTextView::EnvironmentTextView(int xPosition, int yPosition, float val):xPos{xPosition}, yPos{yPosition}, value{val}
{
    if(value==std::numeric_limits<float>::infinity())
        environment = "+";//wall
    else
        environment = ".";
}

EnvironmentTextView::~EnvironmentTextView()
{

}

std::string EnvironmentTextView::getEnvironment() const
{
    return environment;
}
