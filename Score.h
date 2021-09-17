#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
private:
    Score(QGraphicsItem * parent=0);
    static Score * _oScore;

    int _score;

public:
    // "Constructor"
    static Score * oScore();

    //increase score //  _score++
    void increase();
    void decrease();

    //getter
    int score();

};

#endif // SCORE_H
