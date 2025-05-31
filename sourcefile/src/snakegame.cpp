#include "snakegame.h"
#include "soundmanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include "skin.h"
#include <QIcon>

SnakeGame::SnakeGame(QWidget *parent)
    : QMainWindow(parent), score(0), gameOver(false), snake(nullptr), food(nullptr), 
      gameRenderer(nullptr), gameTimer(nullptr), currentDifficulty(Difficulty::MEDIUM)
{
    try {
        setWindowTitle("贪吃蛇游戏");
        setWindowIcon(QIcon(":/resources/snake_icon.png"));
        // 默认皮肤：黑色背景，深绿色蛇头，绿色蛇身，红色食物
        currentSkin = {"经典", QColor(0,0,0), QColor(0,128,0), QColor(144, 238, 144), QColor(255,0,0), SkinShape::RECTANGLE};
        
        // 创建游戏组件
        gameRenderer = new GameRenderer(this);
        if (!gameRenderer) {
            throw std::runtime_error("无法创建游戏渲染器");
        }
        setCentralWidget(gameRenderer);
        
        // 同步皮肤到渲染器
        gameRenderer->setSkin(currentSkin);
        
        // 创建定时器
        gameTimer = new QTimer(this);
        if (!gameTimer) {
            throw std::runtime_error("无法创建游戏定时器");
        }
        connect(gameTimer, &QTimer::timeout, this, &SnakeGame::updateGame);
        
        // 初始化游戏
        initGame();
        
        qDebug() << "游戏初始化完成";
    } catch (const std::exception& e) {
        qDebug() << "游戏初始化失败:" << e.what();
        throw;
    }
}

SnakeGame::~SnakeGame()
{
    try {
        // 停止定时器
        if (gameTimer) {
            gameTimer->stop();
            // 不需要手动删除，Qt的父子对象机制会自动处理
        }
        
        // 不需要手动删除其他对象，Qt的父子对象机制会自动处理
        qDebug() << "游戏资源清理完成";
    } catch (const std::exception& e) {
        qDebug() << "游戏资源清理失败:" << e.what();
    }
}

void SnakeGame::setDifficulty(Difficulty difficulty)
{
    currentDifficulty = difficulty;
    if (gameTimer && gameTimer->isActive()) {
        gameTimer->setInterval(getGameSpeed());
        // 更新背景音乐
        SoundManager::getInstance().playBackgroundMusic(difficulty);
    }
}

int SnakeGame::getGameSpeed() const
{
    switch (currentDifficulty) {
        case Difficulty::EASY:
            return 200;  // 较慢
        case Difficulty::MEDIUM:
            return 100;  // 中速
        case Difficulty::HARD:
            return 50;   // 较快
        default:
            return 100;
    }
}

void SnakeGame::initGame()
{
    try {
        // 初始化游戏状态
        score = 0;
        gameOver = false;
        
        // 删除旧的对象
        if (snake) {
            delete snake;
            snake = nullptr;
        }
        
        if (food) {
            delete food;
            food = nullptr;
        }
        
        // 创建新的蛇和食物
        snake = new Snake(GameRenderer::GRID_WIDTH / 2, GameRenderer::GRID_HEIGHT / 2);
        if (!snake) {
            throw std::runtime_error("无法创建蛇对象");
        }
        
        food = new Food();
        if (!food) {
            throw std::runtime_error("无法创建食物对象");
        }
        food->generateNewPosition(GameRenderer::GRID_WIDTH, GameRenderer::GRID_HEIGHT, snake->getBody());
        
        // 更新渲染器
        gameRenderer->setSnake(snake);
        gameRenderer->setFood(food);
        gameRenderer->setScore(score);
        gameRenderer->setGameOver(gameOver);
        
        // 同步皮肤到渲染器
        gameRenderer->setSkin(currentSkin);
        
        // 启动游戏
        gameTimer->start(getGameSpeed());
        
        // 播放背景音乐
        SoundManager::getInstance().playBackgroundMusic(currentDifficulty);
        
        qDebug() << "游戏状态初始化完成";
    } catch (const std::exception& e) {
        qDebug() << "游戏状态初始化失败:" << e.what();
        throw;
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();  // 关闭游戏窗口，这会触发closeEvent
        return;
    }

    if (gameOver) {
        if (event->key() == Qt::Key_R) {
            restartGame();
        }
        return;
    }
    
    switch (event->key()) {
        case Qt::Key_Up:
            snake->changeDirection(Direction::UP);
            break;
        case Qt::Key_Down:
            snake->changeDirection(Direction::DOWN);
            break;
        case Qt::Key_Left:
            snake->changeDirection(Direction::LEFT);
            break;
        case Qt::Key_Right:
            snake->changeDirection(Direction::RIGHT);
            break;
    }
}

void SnakeGame::updateGame()
{
    if (gameOver) return;
    
    snake->move();
    checkCollisions();
    gameRenderer->update();
}

void SnakeGame::checkCollisions()
{
    QPoint head = snake->getHead();
    
    // 检查是否撞墙
    if (head.x() < 0 || head.x() >= GameRenderer::GRID_WIDTH ||
        head.y() < 0 || head.y() >= GameRenderer::GRID_HEIGHT) {
        gameOver = true;
        gameTimer->stop();
        gameRenderer->setGameOver(true);
        SoundManager::getInstance().playGameOverSound();
        return;
    }
    
    // 检查是否撞到自己
    if (snake->checkSelfCollision()) {
        gameOver = true;
        gameTimer->stop();
        gameRenderer->setGameOver(true);
        SoundManager::getInstance().playGameOverSound();
        return;
    }
    
    // 检查是否吃到食物
    if (head == food->getPosition()) {
        snake->grow();
        score += 10;
        gameRenderer->setScore(score);
        food->generateNewPosition(GameRenderer::GRID_WIDTH, GameRenderer::GRID_HEIGHT, snake->getBody());
        SoundManager::getInstance().playEatSound();
    }
}

void SnakeGame::restartGame()
{
    initGame();
}

void SnakeGame::closeEvent(QCloseEvent *event)
{
    SoundManager::getInstance().stopBackgroundMusic();
    emit closed();
    event->accept();
}

void SnakeGame::setSkin(const Skin& skin) {
    currentSkin = skin;
    if (gameRenderer) {
        gameRenderer->setSkin(currentSkin);
        gameRenderer->update();
    }
}

Skin SnakeGame::getCurrentSkin() const {
    return currentSkin;
} 