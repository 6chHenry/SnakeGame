#ifndef SNAKE_H
#define SNAKE_H

#include <QVector>
#include <QPoint>
#include <QKeyEvent>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake(int startX, int startY);
    
    void move();
    void grow();
    bool checkCollision(const QPoint& point) const;
    bool checkSelfCollision() const;
    void changeDirection(Direction newDirection);
    
    const QVector<QPoint>& getBody() const { return body; }
    Direction getDirection() const { return currentDirection; }
    QPoint getHead() const { return body.first(); }
    
private:
    QVector<QPoint> body;
    Direction currentDirection;
    static const int INITIAL_LENGTH = 3;
};

#endif // SNAKE_H 