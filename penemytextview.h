#ifndef PENEMYTEXTVIEW_H
#define PENEMYTEXTVIEW_H
#include "world.h"

class PEnemyTextView: public QObject
{
    Q_OBJECT
public:
    PEnemyTextView(int xPosition, int yPosition);
    virtual ~PEnemyTextView();
    int getXPos() const;
    int getYPos() const;
    std::string getPEnemy() const;

public slots:
    void dead_slot();

private:
    int xPos,yPos;
    float posion;
    std::string penemy;
};

#endif // PENEMYTEXTVIEW_H
