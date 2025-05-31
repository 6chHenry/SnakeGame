#include "gamerenderer.h"
#include <QPainter>
#include <QDebug>
#include "skin.h"

GameRenderer::GameRenderer(QWidget *parent)
    : QWidget(parent), snake(nullptr), food(nullptr), score(0), gameOver(false)
{
    try {
        setFixedSize(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
        setFocusPolicy(Qt::StrongFocus);
        
        // 设置背景色
        setAutoFillBackground(true);
        QPalette pal = palette();
        pal.setColor(QPalette::Window, Qt::black);
        setPalette(pal);
        
        qDebug() << "渲染器初始化完成";
    } catch (const std::exception& e) {
        qDebug() << "渲染器初始化失败:" << e.what();
        throw;
    }
}

GameRenderer::~GameRenderer()
{
    // 不需要手动删除对象，Qt的父子对象机制会自动处理
    qDebug() << "渲染器资源清理完成";
}

void GameRenderer::setSkin(const Skin& skin) {
    currentSkin = skin;
    update();
}

void GameRenderer::paintEvent(QPaintEvent *event)
{
    try {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        
        // 背景
        painter.fillRect(rect(), currentSkin.backgroundColor);
        
        // 绘制网格
        drawGrid(painter);
        
        // 绘制蛇
        if (snake) {
            drawSnake(painter);
        }
        
        // 绘制食物
        if (food) {
            drawFood(painter);
        }
        
        // 绘制分数
        drawScore(painter);
        
        // 如果游戏结束，绘制游戏结束信息
        if (gameOver) {
            drawGameOver(painter);
        }
        
        qDebug() << "渲染完成";
    } catch (const std::exception& e) {
        qDebug() << "渲染失败:" << e.what();
    }
}

void GameRenderer::drawGrid(QPainter& painter)
{
    painter.setPen(QPen(Qt::darkGray));
    for (int i = 0; i <= GRID_WIDTH; ++i) {
        painter.drawLine(i * CELL_SIZE, 0, i * CELL_SIZE, height());
    }
    for (int i = 0; i <= GRID_HEIGHT; ++i) {
        painter.drawLine(0, i * CELL_SIZE, width(), i * CELL_SIZE);
    }
}

void GameRenderer::drawSnake(QPainter& painter)
{
    const QVector<QPoint>& body = snake->getBody();
    for (int i = 0; i < body.size(); ++i) {
        if (i == 0) {
            // 蛇头用不同颜色
            painter.setBrush(currentSkin.snakeColor);
        } else {
            painter.setBrush(currentSkin.snakeBodyColor); // 使用 currentSkin.snakeBodyColor
        }
        QRect cell(body[i].x() * CELL_SIZE,
                   body[i].y() * CELL_SIZE,
                   CELL_SIZE, CELL_SIZE);
        switch (currentSkin.shape) {
            case SkinShape::RECTANGLE:
                painter.drawRect(cell);
                break;
            case SkinShape::CIRCLE:
                painter.drawEllipse(cell);
                break;
            case SkinShape::TRIANGLE: {
                QPolygon triangle;
                triangle << QPoint(cell.center().x(), cell.top())
                         << QPoint(cell.left(), cell.bottom())
                         << QPoint(cell.right(), cell.bottom());
                painter.drawPolygon(triangle);
                break;
            }
        }
    }
}

void GameRenderer::drawFood(QPainter& painter)
{
    painter.setBrush(currentSkin.foodColor);
    painter.setPen(Qt::NoPen);
    QRect foodCell(food->getPosition().x() * CELL_SIZE, food->getPosition().y() * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.drawEllipse(foodCell);
}

void GameRenderer::drawScore(QPainter& painter)
{
    // 根据背景颜色设置得分文本颜色
    if (currentSkin.backgroundColor == Qt::white) {
        painter.setPen(Qt::black); // 如果背景是白色，则文本为黑色
    } else {
        painter.setPen(Qt::white); // 否则文本为白色
    }
    painter.setFont(QFont("Arial", 18));
    painter.drawText(10, 60, QString("得分: %1").arg(score));
}

void GameRenderer::drawGameOver(QPainter& painter)
{
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    QString gameOverText = "游戏结束!\n按R键重新开始";
    QRect textRect = rect();
    painter.drawText(textRect, Qt::AlignCenter, gameOverText);
} 