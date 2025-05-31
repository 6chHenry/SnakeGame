#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <QVector>
#include <QRandomGenerator>

class Food {
public:
    Food();
    
    void generateNewPosition(int maxX, int maxY, const QVector<QPoint>& snakeBody);
    const QPoint& getPosition() const { return position; }
    
private:
    QPoint position;
};

#endif // FOOD_H 