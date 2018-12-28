#ifndef ENVIRONMENTVIEW_H
#define ENVIRONMENTVIEW_H
#include <QGraphicsPixmapItem>

class EnvironmentView : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnvironmentView(float value);
    virtual ~EnvironmentView() = default;

public slots:
    void poisoned();

private:
    QString url = ":/images/";
    int nr;
};

#endif // ENVIRONMENTVIEW_H
