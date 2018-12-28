#ifndef XENEMYTEXTVIEW_H
#define XENEMYTEXTVIEW_H
#include <QObject>

class XEnemyTextView: public QObject
{
    Q_OBJECT
public:
    XEnemyTextView(int xPosition, int yPosition);
    virtual ~XEnemyTextView();

    int getXPos() const;
    int getYPos() const;
    std::string getXEnemy() const;

signals:
    void updateXEnemyTV_signal(int,int,int,int,std::string);//caught by textview

public slots:
    void updateXEnemyPosition(int x,int y);
    void dead_slot();

private:
    int xPos,yPos;
    std::string xenemy;
};

#endif // XENEMYTEXTVIEW_H
