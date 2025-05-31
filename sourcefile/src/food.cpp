#include "food.h"

Food::Food() : position(0, 0) {}

void Food::generateNewPosition(int maxX, int maxY, const QVector<QPoint>& snakeBody) {
    QPoint newPos;
    do {
        newPos.setX(QRandomGenerator::global()->bounded(maxX));
        newPos.setY(QRandomGenerator::global()->bounded(maxY));
    } while (snakeBody.contains(newPos));
    
    position = newPos;
} 