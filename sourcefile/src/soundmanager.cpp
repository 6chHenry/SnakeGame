#include "soundmanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager(QObject *parent)
    : QObject(parent), muted(false), currentDifficulty(SnakeGame::Difficulty::MEDIUM)
{
    // 设置音效文件路径
    QString soundPath = QCoreApplication::applicationDirPath() + "/sounds/";
    QDir().mkpath(soundPath);  // 确保目录存在

    // 初始化音效
    normalBGM = new QSoundEffect(this);
    hardBGM = new QSoundEffect(this);
    eatSound = new QSoundEffect(this);
    gameOverSound = new QSoundEffect(this);

    // 设置音效文件
    QString normalBgmPath = soundPath + "normal_bgm.wav";
    QString hardBgmPath = soundPath + "hard_bgm.wav";
    QString eatSoundPath = soundPath + "eat.wav";
    QString gameOverSoundPath = soundPath + "gameover.wav";

    normalBGM->setSource(QUrl::fromLocalFile(normalBgmPath));
    hardBGM->setSource(QUrl::fromLocalFile(hardBgmPath));
    eatSound->setSource(QUrl::fromLocalFile(eatSoundPath));
    gameOverSound->setSource(QUrl::fromLocalFile(gameOverSoundPath));

    // 添加调试输出
    qDebug() << "SoundManager Init:";
    qDebug() << "Normal BGM path:" << normalBgmPath << "exists:" << QFileInfo(normalBgmPath).exists() << "status:" << normalBGM->status();
    qDebug() << "Hard BGM path:" << hardBgmPath << "exists:" << QFileInfo(hardBgmPath).exists() << "status:" << hardBGM->status();
    qDebug() << "Eat Sound path:" << eatSoundPath << "exists:" << QFileInfo(eatSoundPath).exists() << "status:" << eatSound->status();
    qDebug() << "Game Over Sound path:" << gameOverSoundPath << "exists:" << QFileInfo(gameOverSoundPath).exists() << "status:" << gameOverSound->status();

    // 设置循环播放
    normalBGM->setLoopCount(QSoundEffect::Infinite);
    hardBGM->setLoopCount(QSoundEffect::Infinite);

    // 设置音量
    normalBGM->setVolume(0.5f);
    hardBGM->setVolume(0.5f);
    eatSound->setVolume(0.7f);
    gameOverSound->setVolume(0.7f);
}

SoundManager::~SoundManager()
{
    stopBackgroundMusic();
}

void SoundManager::playBackgroundMusic(SnakeGame::Difficulty difficulty)
{
    if (muted) return;

    // 如果难度改变，停止当前音乐
    if (currentDifficulty != difficulty) {
        stopBackgroundMusic();
        currentDifficulty = difficulty;
    }

    // 根据难度播放对应的背景音乐
    if (difficulty == SnakeGame::Difficulty::HARD) {
        hardBGM->play();
    } else {
        normalBGM->play();
    }
}

void SoundManager::stopBackgroundMusic()
{
    normalBGM->stop();
    hardBGM->stop();
}

void SoundManager::playEatSound()
{
    if (!muted) {
        eatSound->play();
    }
}

void SoundManager::playGameOverSound()
{
    if (!muted) {
        gameOverSound->play();
    }
}

void SoundManager::setMuted(bool muted)
{
    this->muted = muted;
    if (muted) {
        stopBackgroundMusic();
    } else {
        playBackgroundMusic(currentDifficulty);
    }
}

bool SoundManager::isMuted() const
{
    return muted;
} 