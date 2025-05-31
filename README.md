创建者：刘可唯

作为CS1502H的大作业，实现贪吃蛇游戏。

# 贪吃蛇游戏 (SnakeGame)

这是一个使用 C++ 和 Qt6 框架开发的经典贪吃蛇游戏。

## 目录结构(sourcefile/)

以下是项目主要的源文件和目录结构：

.
├── CMakeLists.txt             # CMake 构建配置文件
├── include/                   # 头文件目录
│   ├── food.h                 # 食物类定义
│   ├── gamerenderer.h         # 游戏渲染类定义
│   ├── menuwindow.h           # 菜单窗口类定义
│   ├── skin.h                 # 皮肤结构和枚举定义
│   ├── snake.h                # 蛇类定义
│   ├── snakegame.h            # 核心游戏逻辑类定义
│   └── soundmanager.h         # 声音管理类定义
├── resources/                 # 资源文件目录 (例如: qrc 文件中引用的图片、样式表、声音文件)
│   ├── sounds/                # 声音文件 (例如: normal_bgm.wav, eat.wav)
│   └── styles/                # QSS 样式表文件 (例如: main.qss)
│   └── snake_icon.png         # 游戏图标
├── src/                       # 源文件目录
│   ├── food.cpp               # 食物类实现
│   ├── gamerenderer.cpp       # 游戏渲染类实现
│   ├── main.cpp               # 程序主入口
│   ├── menuwindow.cpp         # 菜单窗口类实现
│   ├── snake.cpp              # 蛇类实现
│   ├── snakegame.cpp          # 核心游戏逻辑类实现
│   └── soundmanager.cpp       # 声音管理类实现
└── resources.qrc              # Qt 资源集合文件


## 主要组件

* **MenuWindow**: 游戏的主菜单界面，提供开始游戏、选择难度、选择皮肤和退出游戏的选项。
* **SnakeGame**: 游戏的核心逻辑，管理游戏状态、蛇、食物、得分和游戏规则。
* **GameRenderer**: 负责将游戏画面（蛇、食物得分等）渲染到屏幕上。
* **Snake**: 代表玩家控制的蛇，处理移动、生长和碰撞检测。
* **Food**: 代表蛇需要吃的食物，随机生成在地图上。
* **SoundManager**: 管理游戏的背景音乐和各种音效。
* **Skin**: 定义了游戏元素（背景、蛇、食物）的外观。

## 构建与运行

您可以直接运行SnakeGame.exe来开始游戏，所用到的Qt库中的dll文件已经放在根目录下。

项目使用 CMake 进行构建。您需要安装 Qt6 (包含 Core, Gui, Widgets, Multimedia 模块) 和一个支持 C++17 的编译器 (例如 MinGW on Windows)。

1.  配置 CMake 项目，指定 Qt6 的安装路径。
2.  使用 CMake 构建项目。
3.  运行生成的可执行文件。

---

