#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H
#include <QGraphicsPixmapItem>

class HealthPackView: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    HealthPackView();
    virtual ~HealthPackView();

public slots:
    void updates();
    void used_slot();

private:
    int nrOfPic = 4;
    QTimer *timer;

};

#endif // HEALTHPACKVIEW_H
