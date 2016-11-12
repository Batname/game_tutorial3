#ifndef GAME_H
#define GAME_H

#include "hex_board.h"
#include "player_type.h"

#include <QGraphicsView>
#include <QMouseEvent>

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);

    // public methods
    void displayMainMenu();
    PlayerType getWhosTurn();
    void setWhosTurn(PlayerType player);
    void pickUpCard(Hex *card);
    void placeCard(Hex *hex_to_replace);
    void nextPlayersTurn();
    void removeFromDeck(Hex * card, PlayerType player);

    // events
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);

    // public attributes
    QGraphicsScene * scene;
    HexBoard * hex_board;
    QPointF original_position;

public slots:
    void start();

private:
    // private methods
    void drowPanel(int x, int y, int width, int height, QColor color, double opacity);
    void drawGUI();
    void createNewCard(PlayerType player);
    void createInitialCards();
    void drawCards();

    // private  attributes
    PlayerType whos_turn;
    QGraphicsTextItem * whos_turn_text;
    Hex * card_to_place;

    QList<Hex *> player1_cards;
    QList<Hex *> player2_cards;
};

#endif // GAME_H
