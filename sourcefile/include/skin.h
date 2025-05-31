#ifndef SKIN_H
#define SKIN_H

#include <QColor>
#include <QString>

enum class SkinShape {
    RECTANGLE,
    CIRCLE,
    TRIANGLE
};

enum class SkinColor {
    CLASSIC,
    GREEN,
    BLUE,
    RED,
    YELLOW
};

struct Skin {
    QString name;
    QColor backgroundColor;
    QColor snakeColor;
    QColor snakeBodyColor;
    QColor foodColor;
    SkinShape shape;
};

#endif // SKIN_H