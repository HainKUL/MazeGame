#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <world.h>
#include <QObject>
#include <vector>
#include <memory>

class Environment: public QObject, public Tile
{
public:
    Q_OBJECT
public:
    Environment(int xPosition, int yPosition, float tileWeight);
    virtual ~Environment() = default;
    void setVPoisonValue(float newValue);
    float getPoison() const;
    void setPoison(float value);

signals:
    void poiValueChanged();

private:
    float poison;
};

#endif // ENVIRONMENT_H
