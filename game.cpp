#include "game.h"
#include "hex_board.h"
#include "button.h"
#include "player_type.h"

#include "stdlib.h" // rand()
#include "time.h" // time()
#include <QGraphicsTextItem>
#include <QDebug>

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

    // initialize
    card_to_place = NULL;
}

void Game::start()
{
    // clear the screen
    scene->clear();

    // test code
    hex_board = new HexBoard;
    hex_board->placeHexes(200, 30, 7, 7);

    drawGUI();
    createInitialCards();
}

void Game::drowPanel(int x, int y, int width, int height, QColor color, double opacity)
{
    // drow panel
    QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
    QBrush bruch;
    bruch.setStyle(Qt::SolidPattern);
    bruch.setColor(color);
    panel->setBrush(bruch);
    panel->setOpacity(opacity);

    scene->addItem(panel);
}

void Game::drawGUI()
{
    // drow the left panel
    drowPanel(0, 0, 150, 768, Qt::darkCyan, 0.5);

    // draw the right panel
    drowPanel(874, 0, 150, 768, Qt::darkCyan, 0.5);

    // place player one text
    QGraphicsTextItem * p1 = new QGraphicsTextItem("Player 1's cards");
    p1->setPos(25, 0);
    scene->addItem(p1);

    // place player two text
    QGraphicsTextItem * p2 = new QGraphicsTextItem("Player 2's cards");
    p2->setPos(874 + 25, 0);
    scene->addItem(p2);

    // whos tur text
    whos_turn_text = new QGraphicsTextItem;
    setWhosTurn(PlayerType::PLAYER_ONE);
    whos_turn_text->setPos(490,0);
    scene->addItem(whos_turn_text);
}

void Game::createNewCard(PlayerType player)
{
     Hex * card = new Hex;
     card->setOwner(player);
     card->setIsPlaced(false);

     // randommize side attacks of card
     for (size_t i = 0, n = 6; i < n; i++){
         // generate a random number
         int randNum = rand() % 6 + 1; // 1 - 6
         card->setAttackOf(i,randNum);
     }

     // make side attack visible
     card->displaySideAttack();

     // add card to the list
     if (player == PlayerType::PLAYER_ONE){
         player1_cards.append(card);
     }
     else if (player == PlayerType::PLAYER_TWO) {
         player2_cards.append(card);
     }

     // draw the cards
     drawCards();
}

void Game::createInitialCards()
{
    // player 1 cards
    for (size_t i = 0, n = 5; i < n; ++i) {
        createNewCard(PlayerType::PLAYER_ONE);
    }

    // player 2 cards
    for (size_t i = 0, n = 5; i < n; ++i) {
        createNewCard(PlayerType::PLAYER_TWO);
    }

    // draw cards
    drawCards();
}

void Game::drawCards()
{
    // remove player 1 cards
    for (size_t i = 0, n = player1_cards.size(); i < n; ++i) {
        // if (player1_cards[i]->type() == QGraphicsItem::Type)
        scene->removeItem(player1_cards[i]);
    }

    // remove player 2 cards
    for (size_t i = 0, n = player2_cards.size(); i < n; ++i) {
        // if (player1_cards[i]->type() == QGraphicsItem::Type)
        scene->removeItem(player2_cards[i]);
    }

    // draw player 1 cards
    for (size_t i = 0, n = player1_cards.size(); i < n; ++i) {
        Hex * card = player1_cards[i];
        card->setPos(13, 25 + 85 * i);
        scene->addItem(card);
    }

    // draw player 2 cards
    for (size_t i = 0, n = player2_cards.size(); i < n; ++i) {
        Hex * card = player2_cards[i];
        card->setPos(874 + 13, 25 + 85 * i);
        scene->addItem(card);
    }
}

void Game::displayMainMenu()
{
    // create title
    QGraphicsTextItem * title_text = new QGraphicsTextItem(QString("Hex War"));
    QFont title_font("comic sans", 50);
    title_text->setFont(title_font);

    int tx_pos = this->width() / 2 - title_text->boundingRect().width() / 2;
    int ty_pos = 150;

    title_text->setPos(tx_pos, ty_pos);

    scene->addItem(title_text);

    // Create play button
    Button * play_button = new Button(QString("Play"));
    int bx_pos = this->width() / 2 - play_button->boundingRect().width() / 2;
    int by_pos = 275;
    play_button->setPos(bx_pos, by_pos);
    connect(play_button, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(play_button);

    // Create quit button
    Button * quit_button = new Button(QString("Quit"));
    int qx_pos = this->width() / 2 - quit_button->boundingRect().width() / 2;
    int qy_pos = 350;
    quit_button->setPos(qx_pos, qy_pos);
    connect(quit_button, SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quit_button);
}

PlayerType Game::getWhosTurn()
{
    return whos_turn;
}

void Game::setWhosTurn(PlayerType player)
{
    whos_turn = player;

    // change text
    QString text;

    if (player == PlayerType::PLAYER_ONE)
        text = QString("Whos turn: player1");
    else if (player == PlayerType::PLAYER_TWO)
        text = QString("Whos turn: player2");

    whos_turn_text->setPlainText(text);

}

void Game::pickUpCard(Hex *card)
{
    // pick card
    if (card->getOwner() == getWhosTurn() && card_to_place == NULL) {
        card_to_place = card;
        original_position = card->pos();
    }
}

void Game::placeCard(Hex *hex_to_replace)
{
    card_to_place->setPos(hex_to_replace->pos());
    hex_board->getHexes().removeAll(hex_to_replace);
    hex_board->getHexes().append(card_to_place);
    scene->removeItem(hex_to_replace);
    card_to_place->setIsPlaced(true);
    removeFromDeck(card_to_place, getWhosTurn());

    // find neighbors
    card_to_place->findNeighbors();
    card_to_place->captureNaighbors();

    card_to_place = NULL;

    // replace new card
    createNewCard(getWhosTurn());

    nextPlayersTurn();
}

void Game::nextPlayersTurn()
{
    if (whos_turn == PlayerType::PLAYER_ONE) {
        setWhosTurn(PlayerType::PLAYER_TWO);
    } else {
        setWhosTurn(PlayerType::PLAYER_ONE);
    }
}

void Game::removeFromDeck(Hex *card, PlayerType player)
{
    if (player == PlayerType::PLAYER_ONE) {
        player1_cards.removeAll(card);
    } else if (player == PlayerType::PLAYER_TWO) {
        player2_cards.removeAll(card);
    }
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (card_to_place) {
        card_to_place->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event)
{
    //  right click to original
    if (event->button() == Qt::RightButton) {
        if (card_to_place) {
            card_to_place->setPos(original_position);
            card_to_place = NULL;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
