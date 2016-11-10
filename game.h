#ifndef GAME_H
#define GAME_H

#include "hex_board.h"

#include <QGraphicsView>

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent=0);
    void start();

    QGraphicsScene * scene;
    HexBoard * hex_board;
    QString whos_turn;
private:
};

#endif // GAME_H
