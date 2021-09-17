#include <QGraphicsScene>
#include <QApplication>
#include <QObject>
#include <Player.h>
#include <QGraphicsView>
#include <QTimer>
#include <Game.h>


Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
