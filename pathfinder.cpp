
#include "pathfinder.h"
#include <iostream>
#include <vector>
#include <utility>
#include <QDebug>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "environment.h"

bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator <(GridLocation a, GridLocation b) {
  return a.priority<b.priority;
}

bool operator >(GridLocation a, GridLocation b) {
  return a.priority>b.priority;
}

bool Pathfinder::passable(GridLocation& grid)
{
    return !std::isinf(grid.value);
}

bool Pathfinder::isValidPosition(GridLocation grid)
{
  return !getNeighbors(grid).empty();
}

std::vector<GridLocation> Pathfinder::getPath() const
{
    return path;
}

float Pathfinder::getWeight() const
{
    return weight;
}

void Pathfinder::setWeight(float value)
{
    weight = value;
}

std::vector<GridLocation> Pathfinder::getMap() const
{
    return map;
}

GridLocation Pathfinder::getMystart() const
{
    return mystart;
}

void Pathfinder::setMystart(const GridLocation &value)
{
    mystart = value;
}

GridLocation Pathfinder::getGoal() const
{
    return goal;
}

//set the
void Pathfinder:: setStart(int x,int y)
{
    mystart=map.at(x+y*cols);
}

//set the value of tile to infinity
void Pathfinder::setInf(unsigned long index)
{
    map.at(index).value=std::numeric_limits<float>::infinity();
}

void Pathfinder::setGoal(int x, int y)
{
    goal = map.at(x+y*cols);
}

void Pathfinder::setGoal(const GridLocation &value)
{
    goal = value;
}

void Pathfinder::setGcost(float value)
{
    Gcost = value;
}

void Pathfinder::setValue(unsigned long index, float val)
{
    map.at(index).value=val;
}



//initialise the map
Pathfinder::Pathfinder(std::vector<std::unique_ptr<Environment>>& mmap,int mwidth, int mlength):cols{mwidth},rows{mlength}
{
    // initialise the map and store in a vector
    for(int i=0;i<mlength;i++)
    {
        for(int j=0;j<mwidth;j++)
        {
           int xPos=mmap.at(i*mwidth+j)->getXPos();

           int yPos=mmap.at(i*mwidth+j)->getYPos();
           float value=mmap.at(i*mwidth+j)->getValue();
           //std::vector<unsigned long>vector(4);
           GridLocation grid{0,0,xPos,yPos,value,0,0};
           map.push_back(grid);
        }
    }
}


//initialise the map
Pathfinder::Pathfinder(std::vector<std::unique_ptr<Tile>>& mmap,int mwidth,int mlength):cols{mwidth},rows{mlength}
{
    for(int i=0;i<mlength;i++)
    {
        for(int j=0;j<mwidth;j++)
        {
           int xPos=mmap.at(i*mwidth+j)->getXPos();

           int yPos=mmap.at(i*mwidth+j)->getYPos();
           float value=mmap.at(i*mwidth+j)->getValue();
           //std::vector<unsigned long>vector(4);
           GridLocation grid{0,0,xPos,yPos,value,0,0};
           map.push_back(grid);
        }
    }
}

Pathfinder::~Pathfinder()
{}


// use a_star algorithm to search path
//find valid path --> return true
//no valid path--> return false
bool Pathfinder::find()
{

    path.clear();
    std::priority_queue<GridLocation,std::vector<GridLocation>,std::greater<GridLocation>> frontier;

    //check if it is a valid  destination
    if(!isValidPosition(goal)){
      qDebug()<<"the goal is not reachable, exiting! Please choose a valid position";
      return false;
    }

    //check if it is a valid  start
    if(!isValidPosition(mystart)){
      qDebug()<< "Failed to proceed: the starting point is surrounded by walls, exiting! Please choose a valid position";
      return false;
    }

    frontier.push(mystart);

    // start the main loop for the search
    while (!frontier.empty()) {
        GridLocation current=frontier.top();
        frontier.pop();
        unsigned long index_current=(unsigned long)current.x+current.y*cols;
        if(current==goal)   //check the exit condition
        {
            //qDebug()<<"find goal" ;
            //qDebug()<<"x= "<<current.x<< " y= "<<current.y ;
            //qDebug()<<"x: "<<map[current.come_from].x<<" y: "<< map[current.come_from].y ;
            return true;
        }
          std::vector<unsigned long> neighbors=getNeighbors(current);
          //iterate the all the elements in the neighbors
          for(auto index:neighbors)
          {
              GridLocation * next=& map[index];
              float new_cost=current.cost+current.value-next->value+Gcost;
              float heuristic=abs(goal.x-next->x)+abs(goal.y-next->y);
              float priority =new_cost+weight*heuristic;

              if(next->visited==0||(next->visited==1&&new_cost<next->cost))
              {
                    next->cost=new_cost;//update the minimum total cost from start to this gridlocation
                    next->come_from=index_current; // update the previous gridlocation of this point
                    next->priority=priority;
                    frontier.push(map[index]);
                    if(next->visited==0)next->visited=1;
              }
          }
    }
    return false;
}

bool Pathfinder::find(std::unique_ptr<Environment>& start, std::unique_ptr<Environment>& end)
{
    mystart=GridLocation{0,0,start->getXPos(),start->getYPos(),start->getValue(),0,0};
    goal=GridLocation{0,0,end->getXPos(),end->getYPos(),end->getValue(),0,0};
    return find();
}


//generate the path for the search
//clear the info of previous search
void Pathfinder::generatePath()
{
        GridLocation current=map[goal.x+goal.y*cols];
        path.push_back(map[goal.x+goal.y*cols]);
        while(current!=mystart)
        {
            path.push_back(map[current.come_from]);
            //qDebug()<<"x= "<<current.x<< "  y= "<< current.y<<"  came from "<<current.come_from ;
            current=map[current.come_from];
        }

        std::reverse(path.begin(),path.end());

        //clear all info about previous search
        for (auto & gl:map)
        {
            gl.come_from=0;
            gl.cost=0;
            gl.visited=0;
        }
}

std::vector<unsigned long> Pathfinder:: getNeighbors(GridLocation current)
{
    std::vector<unsigned long> neighbors;
    int xPos=current.x;
    int yPos=current.y;
    //check if current GridLocation is in the first column
    if(xPos>=1)
    {
        if(passable(map[yPos*cols+xPos-1]))
        neighbors.push_back((unsigned long)(yPos*cols+xPos-1));
    }

     //check if current GridLocation is in the last column
    if(xPos<cols-1)
    {
        if(passable(map[yPos*cols+xPos+1]))
        neighbors.push_back((unsigned long)(yPos*cols+xPos+1));
    }

      //check if current GridLocation is in the first row
    if(yPos>=1)
    {
        if(passable(map[yPos*cols+xPos-cols]))
        neighbors.push_back((unsigned long)(yPos-1)*cols+xPos);
    }

      //check if current GridLocation is in the last row
    if(yPos<rows-1)
    {
        if(passable(map[yPos*cols+xPos+cols]))
        neighbors.push_back((unsigned long)((yPos+1)*cols+xPos));
    }
    return neighbors;
}


