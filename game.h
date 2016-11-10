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

    QString getWhosTurn();
    void setWhosTurn(QString player);

    QGraphicsScene * scene;
    HexBoard * hex_board;

public slots:
    void start();

private:
    void drowPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();

    QString whos_turn;
    QGraphicsTextItem * whos_turn_text;
};

#endif // GAME_H
