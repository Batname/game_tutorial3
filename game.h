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
    // private methods
    void drowPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(QString player);
    void createInitialCards();
    void drawCards();

    // private  attributes
    QString whos_turn;
    QGraphicsTextItem * whos_turn_text;

    QList<Hex *> player1_cards;
    QList<Hex *> player2_cards;
};

#endif // GAME_H
