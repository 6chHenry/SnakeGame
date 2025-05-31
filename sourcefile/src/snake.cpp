#include "snake.h"

Snake::Snake(int startX, int startY) : currentDirection(Direction::RIGHT) {
    // 初始化蛇身
    for (int i = 0; i < INITIAL_LENGTH; ++i) {
        body.append(QPoint(startX - i, startY));
    }
}

void Snake::move() {
    QPoint newHead = body.first();
    
    switch (currentDirection) {
        case Direction::UP:
            newHead.setY(newHead.y() - 1);
            break;
        case Direction::DOWN:
            newHead.setY(newHead.y() + 1);
            break;
        case Direction::LEFT:
            newHead.setX(newHead.x() - 1);
            break;
        case Direction::RIGHT:
            newHead.setX(newHead.x() + 1);
            break;
    }
    
    body.prepend(newHead);
    body.removeLast();
}

void Snake::grow() {
    QPoint tail = body.last();
    body.append(tail);
}

bool Snake::checkCollision(const QPoint& point) const {
    return body.contains(point);
}

bool Snake::checkSelfCollision() const {
    QPoint head = body.first();
    for (int i = 1; i < body.size(); ++i) {
        if (body[i] == head) {
            return true;
        }
    }
    return false;
}

void Snake::changeDirection(Direction newDirection) {
    // 防止180度转向
    if ((currentDirection == Direction::UP && newDirection == Direction::DOWN) ||
        (currentDirection == Direction::DOWN && newDirection == Direction::UP) ||
        (currentDirection == Direction::LEFT && newDirection == Direction::RIGHT) ||
        (currentDirection == Direction::RIGHT && newDirection == Direction::LEFT)) {
        return;
    }
    currentDirection = newDirection;
} 