#include "game.h"

#include <QGraphicsScene>

Game::Game(QWidget *parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    // set up the scene
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
}
