#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "model.h"
#include "protagonisttextview.h"
#include "penemytextview.h"
#include "enemytextview.h"
#include "environmenttextview.h"
#include "healthpacktextview.h"
#include "xenemytextview.h"

class TextView: public QObject
{
    Q_OBJECT
public:
    TextView(std::shared_ptr<Model> &m);
    void initTextView();
    void draw();
    void redraw();

signals:
    void redraw_textbrowser(QString str);

public slots:
    //protag slots
    void updateProtagPosition(int x,int y);
    //xenemy slots
    void updateXEnemyTV_slot(int oldX,int oldY,int newX,int newY,std::string xenemy);//receive signal from xenemytextview class

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ProtagonistTextView> tvProtag;
    std::vector<std::shared_ptr<EnemyTextView>> tvEnemies;
    std::vector<std::shared_ptr<PEnemyTextView>> tvPEnemies;
    std::vector<std::shared_ptr<XEnemyTextView>> tvXEnemies;
    std::vector<std::shared_ptr<EnvironmentTextView>> tvEnvironments;
    std::vector<std::shared_ptr<HealthPackTextView>> tvHealthPacks;
    int rows,cols;
    std::vector<std::string> tiles;
};

#endif // TEXTVIEW_H
