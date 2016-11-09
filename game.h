#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent=0);
    void start();

    QGraphicsScene * scene;
    // HexBoard * hexBord; TODO
    QString whos_turn;
private:
};

#endif // GAME_H
