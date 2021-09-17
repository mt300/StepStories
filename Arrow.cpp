#include "Arrow.h"
#include <Game.h>

extern Game * game;

Arrow::Arrow(int speed, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // initializing the arrow value UP , DOWN, LEFT or RIGHT
    _value = randValue();

    // getting the singleton score
    score = Score::oScore();

    // draw an arrow
    setPixmap(QPixmap(":/images/arrow_2.png"));

    // rotate the arrow to keep only one arrow file resource
    setTransformOriginPoint(25,25);
    setRotation(_value);

    //make it move
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    //start the timer -> 1 move() each 'speed' miliseconds
    // note that's in constructor so we can't change speed here during movement
    timer->start(speed);
}


void Arrow::destroy()
{
    emit outFocus();            //take it out the focus list
    scene()->removeItem(this);  // remove arrow from the scene
    delete this;                //delete arrow
}

int Arrow::value()
{
    return _value;
}

int Arrow::randValue()
{
    int index = rand() % 4;
    int values[4] = {LEFT_KEY,RIGHT_KEY,UP_KEY,DOWN_KEY};
    return values[index];
}


void Arrow::move()
{
    // setting focus if it's inside player square
    if(pos().y() == Y_PLAYER)
    {
        emit intoFocus(this);
    }
    // destroyn arrow if it's getting out the player square
    if(pos().y() > Y_PLAYER + H_PLAYER - H_ARROW)
    {
        score->decrease();
        destroy();
        return;
    }

    setPos(x(),y()+10);
    //setRotation(rotation() + 15);
}
