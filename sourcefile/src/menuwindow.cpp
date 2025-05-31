#include "menuwindow.h"
#include <QFont>
#include <QApplication>
#include "skin.h"
#include "snakegame.h"
#include <optional>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QButtonGroup>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent), gameWindow(nullptr), currentDifficulty(SnakeGame::Difficulty::MEDIUM)
{
    // 设置窗口标题和大小
    setWindowTitle("贪吃蛇游戏");
    setWindowIcon(QIcon(":/resources/snake_icon.png"));
    resize(600, 600);

    // 创建中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主布局
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setSpacing(20);

    // 创建标题标签
    titleLabel = new QLabel("CS1502H：贪吃蛇\n组员：刘可唯、任宇轩、董彦慷、李政澔", this);
    QFont titleFont("Arial", 20, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // 创建所有按钮的通用字体
    QFont buttonFont("Arial", 18);

    // 创建难度选择按钮组
    difficultyGroup = new QButtonGroup(this);
    
    // 创建简单难度按钮
    easyButton = new QPushButton("简单", this);
    easyButton->setMinimumSize(150, 40);
    easyButton->setCheckable(true);
    easyButton->setFont(buttonFont);
    difficultyGroup->addButton(easyButton, 0);
    
    // 创建中等难度按钮
    mediumButton = new QPushButton("中等", this);
    mediumButton->setMinimumSize(150, 40);
    mediumButton->setCheckable(true);
    mediumButton->setChecked(true);  // 默认选中中等难度
    mediumButton->setFont(buttonFont);
    difficultyGroup->addButton(mediumButton, 1);
    
    // 创建困难难度按钮
    hardButton = new QPushButton("困难", this);
    hardButton->setMinimumSize(150, 40);
    hardButton->setCheckable(true);
    hardButton->setFont(buttonFont);
    difficultyGroup->addButton(hardButton, 2);

    // 创建难度按钮的水平布局
    QHBoxLayout *difficultyLayout = new QHBoxLayout();
    difficultyLayout->addWidget(easyButton);
    difficultyLayout->addWidget(mediumButton);
    difficultyLayout->addWidget(hardButton);
    difficultyLayout->setSpacing(10);
    mainLayout->addLayout(difficultyLayout);

    // 创建开始游戏按钮
    startButton = new QPushButton("开始游戏", this);
    startButton->setMinimumSize(200, 50);
    startButton->setFont(buttonFont);
    mainLayout->addWidget(startButton);

    // 创建退出游戏按钮
    exitButton = new QPushButton("退出游戏", this);
    exitButton->setMinimumSize(200, 50);
    exitButton->setFont(buttonFont);
    mainLayout->addWidget(exitButton);

    // 创建皮肤选择按钮组
    skinGroup = new QButtonGroup(this); // 初始化 skinGroup
    skinGroup->setExclusive(true); // 设置互斥选择

    // 只保留两个皮肤按钮
    QPushButton* classicBtn = new QPushButton("经典皮肤");
    classicBtn->setObjectName("classicSkinButton"); // 设置对象名
    classicBtn->setMinimumSize(150, 40);
    classicBtn->setCheckable(true); // 设置为可选中
    classicBtn->setFont(buttonFont);
    skinGroup->addButton(classicBtn, 0); // 添加到按钮组
    
    QPushButton* whiteBtn = new QPushButton("蓝色皮肤");
    whiteBtn->setObjectName("blueSkinButton"); // 设置对象名
    whiteBtn->setMinimumSize(150, 40);
    whiteBtn->setCheckable(true); // 设置为可选中
    whiteBtn->setFont(buttonFont);
    skinGroup->addButton(whiteBtn, 1); // 添加到按钮组

    // 创建皮肤按钮的水平布局
    QHBoxLayout *skinLayout = new QHBoxLayout();
    skinLayout->addWidget(classicBtn);
    skinLayout->addWidget(whiteBtn);
    skinLayout->setSpacing(10);
    mainLayout->addLayout(skinLayout);

    // 默认选中经典皮肤
    classicBtn->setChecked(true);
    // 首次启动时设置默认皮肤
    currentSkin = {"经典", QColor(0,0,0), QColor(0,128,0), QColor(144, 238, 144), QColor(255,0,0), SkinShape::RECTANGLE};

    // 连接皮肤按钮组的信号
    connect(skinGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, [this](int id) {
        Skin skin;
        if (id == 0) { // 经典皮肤
            skin.name = "经典";
            skin.backgroundColor = QColor(0,0,0);
            skin.snakeColor = QColor(0,128,0); // 深绿色蛇头
            skin.snakeBodyColor = QColor(144, 238, 144); // 绿色蛇身 (浅绿色)
            skin.foodColor = QColor(255,0,0);
            skin.shape = SkinShape::RECTANGLE;
        } else if (id == 1) { // 白色皮肤
            skin.name = "白色";
            skin.backgroundColor = QColor(255,255,255);
            skin.snakeColor = QColor(0,0,128); // 蛇头改为深蓝色
            skin.snakeBodyColor = QColor(0,0,255); // 蛇身改为蓝色
            skin.foodColor = QColor(255,0,0);
            skin.shape = SkinShape::RECTANGLE;
        }
        currentSkin = skin;
        emit skinSelected(skin);
        if (gameWindow) gameWindow->setSkin(skin);
    });

    // 连接信号和槽
    connect(startButton, &QPushButton::clicked, this, &MenuWindow::startGame);
    connect(exitButton, &QPushButton::clicked, this, &MenuWindow::exitGame);
    connect(difficultyGroup, &QButtonGroup::idClicked, this, &MenuWindow::difficultyChanged);
}

MenuWindow::~MenuWindow()
{
    if (gameWindow) {
        delete gameWindow;
    }
}

void MenuWindow::difficultyChanged(int id)
{
    switch (id) {
        case 0:
            currentDifficulty = SnakeGame::Difficulty::EASY;
            break;
        case 1:
            currentDifficulty = SnakeGame::Difficulty::MEDIUM;
            break;
        case 2:
            currentDifficulty = SnakeGame::Difficulty::HARD;
            break;
    }
}

void MenuWindow::startGame()
{
    // 创建并显示游戏窗口
    gameWindow = new SnakeGame();
    gameWindow->setDifficulty(currentDifficulty);
    // 重新连接皮肤信号
    disconnect(this, SIGNAL(skinSelected(Skin)), nullptr, nullptr);
    connect(this, &MenuWindow::skinSelected, gameWindow, &SnakeGame::setSkin);
    // 启动时同步一次当前皮肤
    if (currentSkin.has_value()) {
        gameWindow->setSkin(currentSkin.value());
    }
    gameWindow->show();
    this->hide();

    // 当游戏窗口关闭时，显示菜单窗口
    connect(gameWindow, &SnakeGame::closed, this, [this]() {
        this->show();
        delete gameWindow;
        gameWindow = nullptr;
    });
}

void MenuWindow::exitGame()
{
    QApplication::quit();
} 