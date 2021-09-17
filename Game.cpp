#include "Game.h"
#include <QMediaPlayer>



Game::Game(QWidget * parent): QGraphicsView(parent)
{
    //create a Scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,X_SCREEN,Y_SCREEN);

    //setting scene background
    scene->setBackgroundBrush(QBrush(QImage(":/images/bg_1.jpg")));

    //set scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(X_SCREEN,Y_SCREEN);

    //create a player
    player = new Player(0,0);
    player->setPixmap(QPixmap(":/images/player_1.png"));
    player->setPos(X_PLAYER,Y_PLAYER);

    //make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add item to the scene
    scene->addItem(player);

    // create the score
    score = Score::oScore();
    scene->addItem(score);


    // music
   QMediaPlayer * music = new QMediaPlayer();
   music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
   music->play();

    this->show();
}


