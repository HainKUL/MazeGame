#ifndef ENEMYTEXTVIEW_H
#define ENEMYTEXTVIEW_H
#include <QObject>


class EnemyTextView: public QObject
{//penemy and normal enemy share the same textview
    Q_OBJECT
public:
    EnemyTextView(int xPosition, int yPosition);
    virtual ~EnemyTextView();
    int getXPos() const;
    int getYPos() const;
    std::string getEnemy() const;

public slots:
    void dead_slot();

private:
    int xPos, yPos;
    std::string enemy;
};

#endif // ENEMYTEXTVIEW_H
