#ifndef PROTAGONISTTEXTVIEW_H
#define PROTAGONISTTEXTVIEW_H
#include <QObject>


class ProtagonistTextView: public QObject
{
    Q_OBJECT
public:
    ProtagonistTextView(int xPosition, int yPosition);
    virtual ~ProtagonistTextView();

    void updatePosition(int x, int y);
    void updateEnergy(int e);
    void updateHealth(int h);
    int getXPos() const;
    int getYPos() const;
    std::string getProtag() const;

private:
    int xPos,yPos;
    float energy, health;
    std::string protag;
};

#endif // PROTAGONISTTEXTVIEW_H
