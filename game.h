#ifndef GAME_H
#define GAME_H

#include "hex_board.h"

#include <QGraphicsView>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    void displayMainMenu();

    QGraphicsScene * scene;
    HexBoard * hex_board;
    QString whos_turn;
private:

public slots:
    void start();
};

#endif // GAME_H
