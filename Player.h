#ifndef PLAYER_H
#define PLAYER_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <Arrow.h>
#include <Score.h>
#include <fstream>
#include <iostream>
//#include <Jukebox.h>
//#include <Queue.h>
#include <GlobalDefines.h>
#include <QList>
#include <QMediaPlayer>


class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0,int mode=0);
    ~Player(){};

    void setTimer(int time);
    void keyPressEvent(QKeyEvent * event);

    // cheking players command == arrow value
    void matching(int keyValue);

    // CREATOR MODE
    void creator(int keyValue);
    void openFile();
    void closeFile();

    //sounds
    void hitSound();
    void missSound();

public slots:
    // pushBack and pop items from focus list
    void addFocus(Arrow * arrow);
    void removeFocus();

    //spawn arrows
    void spawn();
    void doubleSpawn();

private:
    Score * score;
    QList<Arrow*> focusedItems;
    QMediaPlayer * _hitSound;
    QMediaPlayer * _missSound;
    QTimer * timer;
    std::ofstream file;

    int _mode;
};


#endif // PLAYER_H
