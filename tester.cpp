#include "tester.h"
#include <cmath>
#include <QDebug>

Tester::Tester()
{
   QString url=":/images/maze3.png";
   auto world=std::make_shared<World>();
   pixmap.load(url);
   std::vector<std::unique_ptr<Tile>> tiles;
   tiles=world->createWorld(url);
   int  rowWorld=world->getRows();
   colWorld=world->getCols();
   pathfinder=std::make_shared<Pathfinder>(tiles,colWorld,rowWorld);
   //default setting for A- STAR algorithm
   pathfinder->setGcost(10);
   pathfinder->setWeight(1);
   startSet=false;
   this->addPixmap(pixmap);
}

Tester::~Tester()
{

}



std::shared_ptr<Pathfinder> Tester::getPathfinder() const
{
    return pathfinder;
}

void Tester::drawPath()
{
    //this->removeItem(pixmap);
    this->clear();
    auto path=pathfinder->getPath();
    if(path.size()>0)
    {
       qDebug()<<" draw path";
       QPainter painter(&pixmap);
       painter.setPen(QPen(Qt::red,15));
       qDebug()<<"size of the path :"<<pathfinder->getPath().size();
        for(int i=1;i<path.size();i++)
        {

            //qDebug()<<"x:"<<path[i].x<<"y:"<<path[i].y;
            painter.drawLine(path[i-1].x,path[i-1].y,path[i].x,path[i].y);
        }

        this->addPixmap(pixmap);
    }

    else
    {
        qDebug()<<" No valid path, pathfinding failed";
    }
}

void Tester::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = static_cast<int>(event->scenePos().x());
    int y = static_cast<int>(event->scenePos().y());
    setPos(x,y);
    qDebug()<<x<<","<<y;
}

void Tester::setPos(int x, int y)
{
     //qDebug()<<"setting position" <<x<<","<<y;
    if(startSet==false)//  set the starting point
    {
        qDebug()<<"setting start" <<x<<","<<y;
        pathfinder->setStart(x,y);
        startSet=true;
    }

    else //set the goal point and start search path
    {
        qDebug()<<"setting end point" <<x<<","<<y;
        startSet=false;
        pathfinder->setGoal(x,y);


        clock_t beginTime=clock();// search path and count the elapsed time
        bool result=pathfinder->find();
        clock_t finishTime=clock();
        double elapsed=double (finishTime-beginTime)/CLOCKS_PER_SEC;
        if(result)
        {
            pathfinder->generatePath();
            drawPath();
        }

        else{
            qDebug()<<"No path available";
        }

        qDebug()<<"elapsed time is:"<< elapsed;

    }
}
