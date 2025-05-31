#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "gamerenderer.h"
#include "snake.h"
#include "food.h"
#include "skin.h"

class SnakeGame : public QMainWindow
{
    Q_OBJECT

public:
    enum class Difficulty {
        EASY,
        MEDIUM,
        HARD
    };

    explicit SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

    void setDifficulty(Difficulty difficulty);
    void setSkin(const Skin& skin);
    Skin getCurrentSkin() const;

signals:
    void closed();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void updateGame();
    void restartGame();

private:
    void initGame();
    void checkCollisions();
    int getGameSpeed() const;
    
    GameRenderer *gameRenderer;
    Snake *snake;
    Food *food;
    QTimer *gameTimer;
    int score;
    bool gameOver;
    Difficulty currentDifficulty;
    static const int GRID_SIZE = 20;   // 网格大小
    Skin currentSkin;
};

#endif // SNAKEGAME_H 