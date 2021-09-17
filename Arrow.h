#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <Score.h>

#include <GlobalDefines.h>



class Arrow: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Arrow(int speed=80, QGraphicsItem * parent=0);
    void destroy();

    //gettters
    int value();
    int randValue();

    //increase speed
    /*
        TODO: speed controler
    */

signals:
    void intoFocus(Arrow * arrow);
    void outFocus();

public slots:
    void move();

private:
    int _value;
    Score * score;

};

#endif // ARROW_H
