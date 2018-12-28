#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

extern bool proMoving;
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QString fname, unsigned int nrEnemies, unsigned int nrHPs);
    void createModel(QString fname, unsigned int nrEnemies, unsigned int nrHPs);
    int checkDes(int tempX,int tempY,int posX, int posY);
    int meetEnemy();
    void meetHP(int id);
    int NrAliveEnemies();
    int goToDes(int x,int y);
    void changeTileValue(int layer, int poison);
    void checkTileValue(int x, int y, int poison);
    void bindPEnemy();
    float checkEnergyHealth(int tempX, int tempY, int posX, int posY);
    int ifSolid(int posX, int posY);
    float getScale() const;
    void setScale(float value);
    bool getAutoPlay() const;
    void setAutoPlay(bool value);
    void gameOver();
    bool getPause() const;
    void setPause(bool value);
    float getMaxCost();

signals:
    void sendMessage(QString str);
    void pathGet();
    void loose();
    void win();

public slots:
    void ProtagonistMove_slot(DIRECTION d);
    void PosionedTile_model_slot(int poisonLevel);
    void xEnemyMovingEnemy();
    int strategy();
    void autoPlay_slot();
    void goClickedPos(int x,int y);

public:
    std::shared_ptr<Model> myModel;

private:
    int COL;
    int ROW;
    int current_enemy;
    int poison_state = 1;
    int index=0;
    bool isfinished=false;
    bool autoPlay=false;
    bool pause =false;
    bool fight = true;
    float scale =1.0f;
    int scale_diff = 3;
};

#endif // CONTROLLER_H


