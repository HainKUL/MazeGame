#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "model.h"
#include "environmentview.h"
#include "protagonistview.h"
#include "healthpackview.h"
#include "enemyview.h"
#include "penemyview.h"
#include "xenemy.h"
#include "xenemyview.h"
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(std::shared_ptr<Model> model,QObject *parent = 0);
    virtual ~Scene();
    void addEnvironment();
    void addProtagonist();
    void addHP();
    void addEnemies();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool getTracked() const;
    void setTracked(bool value);
    bool getPause() const;
    void setPause(bool value);

signals:
    void centerMe();

public slots:
    void ProtagonistViewChanged_slot(int x, int y);
    void addPath();

public:
    std::vector<EnvironmentView *> enrvironmentViews;
    std::vector<HealthPackView *> hps;
    std::vector<EnemyView *> enemies;
    std::vector<QGraphicsPixmapItem *> pathView;
    std::vector<PEnemyView *> penemies;
    std::vector<XEnemyView *> xenemies;
    ProtagonistView *proView;

private:
    std::shared_ptr<Model> myModel;
    bool tracked = true;
    int step = 10;
    bool pause = false;
    int len = 50;
};

#endif // SCENE_H
