#ifndef HEALTHPACKTEXTVIEW_H
#define HEALTHPACKTEXTVIEW_H

#include<iostream>
#include <QObject>


class HealthPackTextView: public QObject
{
    Q_OBJECT
public:
    HealthPackTextView(int xPosition, int yPosition);
    std::string getHealthPack() const;
    int getXPos() const;
    int getYPos() const;

public slots:
    void used_slot();

private:
    int xPos,yPos;
    std::string healthPack;
};

#endif // HEALTHPACKTEXTVIEW_H
