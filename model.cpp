#include "model.h"

Model::Model(QString fname, unsigned int nrEnemies, unsigned nrHPs):QObject ()
{
    InitialModel(fname, nrEnemies, nrHPs);
}

void Model::InitialModel(QString fname, unsigned int nrEnemies, unsigned nrHPs)
{
    myWorld = std::make_shared<World>();
    QString filename = fname;
    nrOfEnemies = nrEnemies;
    nrOfXEnemies = static_cast<unsigned int>(nrOfEnemies*0.2);//20% are xenemies
    nrOfPacks = nrHPs;
    myTester=std::make_shared<Tester>();

    //create environment
    worldEnvironment = myWorld->createWorld(filename);
    myEnvironment.reserve(worldEnvironment.size());
    for(auto &p:worldEnvironment){
        auto en = std::make_unique<Environment>(p->getXPos(),p->getYPos(),p->getValue());
        myEnvironment.push_back(std::move(en));
    }

    pathfinder=std::make_shared<Pathfinder>(myEnvironment,myWorld->getCols(),myWorld->getRows());
    worldEnvironment.clear();

    //create enemies
    myEnemies = myWorld->getEnemies(nrOfEnemies);

    //create protagonisit
    myProtagonist = myWorld->getProtagonist();//Tile(0, 0, 0.0f), health{100.0f}, energy{100.0f}

    //create healthpacks
    worldHP.reserve(nrOfPacks);
    worldHP = myWorld->getHealthPacks(nrOfPacks);

    //Type trans
    myHP.reserve(nrOfPacks);
    for(auto &p:worldHP){
        auto pack = std::make_unique<HealthPack>(p->getXPos(),p->getYPos(),p->getValue());
        myHP.push_back(std::move(pack));
    }
    worldHP.clear();

    //create xenemies from normal enemies
    if (nrOfXEnemies==0) nrOfXEnemies =1;
    for(auto &e: myEnemies){
        if(!dynamic_cast<PEnemy *>(e.get())&&nrOfXEnemies>0)
        {//normal enemy
            auto x = std::make_unique<XEnemy>(e->getXPos(),e->getYPos(),e->getValue());
            std::vector<std::unique_ptr<Enemy>>::iterator c_iter = myEnemies.begin();
            std::vector<std::unique_ptr<Enemy>>::iterator c_iter_end = myEnemies.end();
            while(c_iter!= c_iter_end)
            {
            if (e == *c_iter)
            {
                *c_iter = std::move(x);
                nrOfXEnemies--;
            break;
            }
            c_iter++;
            }
        }
    }

    //search for the first non inf tile and give the position to protagonist
    int pro_start =0;
    while(myEnvironment.at(pro_start)->getValue()==std::numeric_limits<float>::infinity()){
        pro_start+=1;
    }
    myProtagonist->setXPos(myEnvironment.at(pro_start)->getXPos());
    myProtagonist->setYPos(myEnvironment.at(pro_start)->getYPos());
}

Enemy * Model:: getNearestEnemy()
{
    int distance=std::numeric_limits<int>::max();
    Enemy* nearest = nullptr;
    for(auto &enemy: myEnemies)
    {
        //int dis=calculateDistance(std::move(enemy));
        int Xdis=abs(myProtagonist->getXPos()-enemy->getXPos());
        int Ydis=abs(myProtagonist->getYPos()-enemy->getYPos());
        if((Xdis+Ydis<distance)&&enemy->getDefeated()==false&&(Xdis+Ydis)>0)
        {
            distance=Xdis+Ydis;
            nearest=enemy.get();
        }
    }

    return nearest;
}


HealthPack *Model::getNearestHP()
{
    int distance=std::numeric_limits<int>::max();
    HealthPack * nearest = nullptr;
    for(auto &hp: myHP)
    {
        //int dis=calculateDistance(std::move(enemy));
        int Xdis=abs(myProtagonist->getXPos()-hp->getXPos());
        int Ydis=abs(myProtagonist->getYPos()-hp->getYPos());
        if(Xdis+Ydis<distance)
        {
            distance=Xdis+Ydis;
            nearest=hp.get();
        }
    }
    return nearest;
}

std::shared_ptr<Tester> Model::getMyTester() const
{
    return myTester;
}

std::shared_ptr<Pathfinder> Model::getPathfinder() const
{
    return pathfinder;
}

void Model::pathGet_slot()
{
    emit refreshPathView();
}

unsigned int Model::getNrOfEnemies() const
{
    return nrOfEnemies;
}

void Model::setNrOfEnemies(unsigned int value)
{
    nrOfEnemies = value;
}

unsigned int Model::getNrOfXEnemies() const
{
    return nrOfXEnemies;
}

void Model::setNrOfXEnemies(unsigned int value)
{
    nrOfXEnemies = value;
}

//slot for received signal from mouse clicked and set the start and end point
void Model::clickedPos(int x, int y)
{
    pathfinder->setGoal(x,y);
    emit goToPos(x,y);
}
