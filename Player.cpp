#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>




Player::Player(QGraphicsItem * parent, int mode): QObject(),QGraphicsPixmapItem(parent)
{
    _mode = mode;
    if(_mode==0)   // default player constructor
    {
        //setting score singleton
        score = Score::oScore();

        // setting timer to spawn new arrows
        timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));

        timer->start(HARD_SPAWN);

        //setting hit sound
        _hitSound = new QMediaPlayer();
        _hitSound->setMedia(QUrl("qrc:/sounds/hitsound.wav"));

        //setting miss sound
        _missSound = new QMediaPlayer();
        _missSound->setMedia(QUrl("qrc:/sounds/misssound.wav"));
    }

    else if (_mode==1)
    {
        //open file
        openFile();
        timer = new QTimer();
        timer->start(208000);
    }

}

// still in progress
void Player::setTimer(int time)
{
    timer->start(time);
}

// getting player(user) keboard commands
void Player::keyPressEvent(QKeyEvent *event)
{
    if (_mode == 0)
    {

        if (event->key() == Qt::Key_Left)
        {
           matching(LEFT_KEY);
           qDebug() << "left";

        }
        else if (event->key() == Qt::Key_Right)
        {
            matching(RIGHT_KEY);
            qDebug() << "right";
        }
        else if (event->key() == Qt::Key_Up)
        {
            matching(UP_KEY);
            qDebug() << "up";
        }
        else if (event->key() == Qt::Key_Down)
        {
            matching(DOWN_KEY);
            qDebug() << "down ";
        }
        else if (event->key() == Qt::Key_Space)
        {
            qDebug() << "space";
        }

    }
    else if(_mode == 1)
    {

        if (event->key() == Qt::Key_Left)
        {
           creator(LEFT_KEY);
           qDebug() << "left";

        }
        else if (event->key() == Qt::Key_Right)
        {
            creator(RIGHT_KEY);
            qDebug() << "right";
        }
        else if (event->key() == Qt::Key_Up)
        {
            creator(UP_KEY);
            qDebug() << "up";
        }
        else if (event->key() == Qt::Key_Down)
        {
            creator(DOWN_KEY);
            qDebug() << "down ";
        }
        else if (event->key() == Qt::Key_Space)
        {
            closeFile();
            qDebug() << "space";
        }

    }
}


void Player::addFocus(Arrow * arrow)
{
    focusedItems.append(arrow);
}

void Player::removeFocus()
{
    focusedItems.pop_front();
}

void Player::matching(int keyValue)
{
    //checking if focusedItems list is not empty
    if(focusedItems.size()==0)
    {
        score->decrease();
        this->missSound();
        return;
    }
    else
    {
        //iterating along the list cheking if there is a Arrow with this value focused
        for(int i=0; i < focusedItems.size(); i++)
        {
            if(focusedItems.at(i) == nullptr)
            {
                qDebug() << "NUll arrow at focus list";
                return;
            }
            //checking if it's hit
            if(keyValue == focusedItems.at(i)->value())
            {
                focusedItems.at(i)->destroy();   // possibly a problem here!! we are
                                                 // poping the last item from list not the one that matches with player command
                this->hitSound();
                score->increase();
                return;
            }
        }
        //if it isn't hit
        score->decrease();
        this->missSound();
    }
}

void Player::creator(int keyValue)
{
    file << keyValue << "," << timer->remainingTime() << std::endl;
}

void Player::openFile()
{
    file.open(FILE_NAME); // ,std::ofstream::app
}

void Player::closeFile()
{
    file.close();
}

void Player::hitSound()
{

    if(_hitSound->state() == QMediaPlayer::PlayingState)
    {
        _hitSound->setPosition(0);
    }
    else if(_hitSound->state() == QMediaPlayer::StoppedState)
    {
        _hitSound->play();
    }
}

void Player::missSound()
{
    if(_missSound->state() == QMediaPlayer::PlayingState)
    {
        _missSound->setPosition(0);
    }
    else if(_missSound->state() == QMediaPlayer::StoppedState)
    {
        _missSound->play();
    }
}


void Player::spawn()
{
    // creating arrow(speed)
    Arrow * arrow = new Arrow(70);
    arrow->setPos(X_ARROW,Y_ARROW);
    scene()->addItem(arrow);

    //connecting Arrows signals to player slots
    connect(arrow,SIGNAL(intoFocus(Arrow*)),this, SLOT(addFocus(Arrow*)));
    connect(arrow,SIGNAL(outFocus()),this, SLOT(removeFocus()));

}

void Player::doubleSpawn()
{
    Arrow * arrowOne = new Arrow(70);
    Arrow * arrowTwo = new Arrow(70);
    arrowOne->setPos(X_ARROW,Y_ARROW);
    arrowTwo->setPos(X_ARROW,Y_ARROW);
    scene()->addItem(arrowOne);
    scene()->addItem(arrowTwo);
    connect(arrowOne,SIGNAL(intoFocus(Arrow*)),this, SLOT(addFocus(Arrow*)));
    connect(arrowTwo,SIGNAL(intoFocus(Arrow*)),this, SLOT(addFocus(Arrow*)));
    connect(arrowOne,SIGNAL(outFocus()),this, SLOT(removeFocus()));
    connect(arrowTwo,SIGNAL(outFocus()),this, SLOT(removeFocus()));
}

