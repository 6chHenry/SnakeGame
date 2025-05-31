#include <QApplication>
#include "menuwindow.h"
#include "soundmanager.h"
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 强制初始化 SoundManager 单例，确保音效资源提前加载
    SoundManager::getInstance();

    // 加载并应用样式表
    QFile styleFile(":/styles/main.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&styleFile);
        app.setStyleSheet(ts.readAll());
        styleFile.close();
    }

    MenuWindow menu;
    menu.show();
    return app.exec();
}