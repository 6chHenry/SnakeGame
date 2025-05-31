#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <QWidget>
#include <QPainter>
#include "snake.h"
#include "food.h"
#include "skin.h"

class GameRenderer : public QWidget {
    Q_OBJECT
    
public:
    static const int CELL_SIZE = 20;
    static const int GRID_WIDTH = 40;
    static const int GRID_HEIGHT = 30;
    
    explicit GameRenderer(QWidget *parent = nullptr);
    ~GameRenderer() override;
    
    void setSnake(Snake* newSnake) { snake = newSnake; }
    void setFood(Food* newFood) { food = newFood; }
    void setScore(int newScore) { score = newScore; }
    void setGameOver(bool isGameOver) { gameOver = isGameOver; }
    void setSkin(const Skin& skin);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    
private:
    Snake* snake;
    Food* food;
    int score;
    bool gameOver;
    Skin currentSkin;
    
    void drawGrid(QPainter& painter);
    void drawSnake(QPainter& painter);
    void drawFood(QPainter& painter);
    void drawScore(QPainter& painter);
    void drawGameOver(QPainter& painter);
};

#endif // GAMERENDERER_H 