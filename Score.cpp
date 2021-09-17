#include "Score.h"
#include <QFont>
#include <QDebug>

Score * Score::_oScore = 0;

Score::Score(QGraphicsItem * parent): QGraphicsTextItem(parent)
{
    _score = 0;

    //Draw the text
    setPlainText(QString("Score: ") + QString::number(_score)); // Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));

}

Score * Score::oScore()
{
    if(_oScore == 0) _oScore = new Score();

    return _oScore;
}


void Score::increase()
{
    _score++;
    setPlainText(QString("Score: ") + QString::number(_score));
}

void Score::decrease()
{
    _score--;
    setPlainText(QString("Score: ") + QString::number(_score));
}

int Score::score()
{
    return _score;
}


