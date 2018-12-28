#ifndef ENVIRONMENTTEXTVIEW_H
#define ENVIRONMENTTEXTVIEW_H
#include <iostream>


class EnvironmentTextView
{
public:
    EnvironmentTextView(int xPosition, int yPosition, float val);
    virtual ~EnvironmentTextView();
    std::string getEnvironment() const;

private:
    int xPos,yPos;
    float value;
    std::string environment;
};

#endif // ENVIRONMENTTEXTVIEW_H
