#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QUrl>
#include "snakegame.h"

class SoundManager : public QObject
{
    Q_OBJECT

public:
    static SoundManager& getInstance();

    void playBackgroundMusic(SnakeGame::Difficulty difficulty);
    void stopBackgroundMusic();
    void playEatSound();
    void playGameOverSound();
    void setMuted(bool muted);
    bool isMuted() const;

private:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();

    QSoundEffect *normalBGM;    // 简单和中等难度的背景音乐
    QSoundEffect *hardBGM;      // 困难难度的背景音乐
    QSoundEffect *eatSound;
    QSoundEffect *gameOverSound;
    bool muted;
    SnakeGame::Difficulty currentDifficulty;
};

#endif // SOUNDMANAGER_H 