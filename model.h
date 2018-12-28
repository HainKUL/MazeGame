#ifndef MODEL_H
#define MODEL_H
#include <memory>
#include "world.h"
#include "config.h"
#include "healthpack.h"
#include "environment.h"
#include "pathfinder.h"
#include "xenemy.h"
#include "tester.h"


class Model : public QObject
{
    Q_OBJECT

public:
    Model(QString fname, unsigned int nrEnemies, unsigned nrHPs);
    void InitialModel(QString fname, unsigned int nrEnemies, unsigned nrHPs);
    std::shared_ptr<Pathfinder> getPathfinder() const;
    Enemy * getNearestEnemy();
    HealthPack * getNearestHP();

    std::shared_ptr<Tester> getMyTester() const;
    unsigned int getNrOfXEnemies() const;
    void setNrOfXEnemies(unsigned int value);
    void clickedPos(int x, int y);

    unsigned int getNrOfEnemies() const;
    void setNrOfEnemies(unsigned int value);

signals:
    void refreshPathView();
    void goToPos(int x,int y);

public slots:
    void pathGet_slot();

public:
    std::shared_ptr<World> myWorld;
    std::vector<std::unique_ptr<Tile>> worldEnvironment;
    std::vector<std::unique_ptr<Environment>> myEnvironment;
    std::unique_ptr<Protagonist> myProtagonist;
    std::vector<std::unique_ptr<Tile>> worldHP;
    std::vector<std::unique_ptr<HealthPack>> myHP;
    std::vector<std::unique_ptr<Enemy>> myEnemies;

private:
    unsigned int nrOfPacks;
    unsigned int nrOfEnemies;
    unsigned int nrOfXEnemies;
    std::shared_ptr<Pathfinder> pathfinder;
    std::shared_ptr<Tester> myTester;
};

#endif // MODEL_H
