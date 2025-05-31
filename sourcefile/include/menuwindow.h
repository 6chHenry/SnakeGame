#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include "snakegame.h"
#include "skin.h"
#include <optional>

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void startGame();
    void exitGame();
    void difficultyChanged(int id);

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QPushButton *startButton;
    QPushButton *exitButton;
    QButtonGroup *difficultyGroup;
    QPushButton *easyButton;
    QPushButton *mediumButton;
    QPushButton *hardButton;
    QButtonGroup *skinGroup;
    SnakeGame *gameWindow;
    SnakeGame::Difficulty currentDifficulty;
    std::optional<Skin> currentSkin;

signals:
    void skinSelected(const Skin& skin);
};

#endif // MENUWINDOW_H 