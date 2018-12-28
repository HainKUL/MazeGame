#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "world.h"
#include <queue>

class Environment;

struct GridLocation {
  float priority;
  float cost;
  int x, y;
  float value;
  unsigned long come_from; //track the index of grid
  int visited;
};

class Pathfinder
{

public:
    Pathfinder();
    ~Pathfinder();

    Pathfinder(std::vector<std::unique_ptr<Tile>>& mmap,int mwidth,int mlength);
    Pathfinder(std::vector<std::unique_ptr<Environment>>& mmap,int mwidth,int mlength);
    bool find(std::unique_ptr<Environment>& start, std::unique_ptr<Environment>& goal);
    bool find();
    void generatePath();
    std::vector<unsigned long> getNeighbors(GridLocation current);
    bool passable(GridLocation& grid);
    bool isValidPosition(GridLocation grid);
    std::vector<GridLocation> getPath() const;
    float getWeight() const;
    void setWeight(float value);
    std::vector<GridLocation> getMap() const;
    GridLocation getMystart() const;
    void setMystart(const GridLocation &value);
    void setStart(int x,int y);
    void setInf(unsigned long index);
    GridLocation getGoal() const;
    void setGoal(const GridLocation &value);
    void setGoal(int x,int y);
    void setGcost(float value);
    void setValue(unsigned long index, float val);

private:
    std::vector<GridLocation> map;
    std::vector<GridLocation> path;
    std::vector<std::vector<unsigned long>> myNeighbors;
    float weight = 1;
    float Gcost = 0;
    GridLocation mystart;
    GridLocation goal;
    int cols, rows;
};

#endif // PATHFINDER_H
