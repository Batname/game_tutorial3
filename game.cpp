#include "game.h"
#include "hex_board.h"
#include "button.h"

#include <QGraphicsTextItem>

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

void Game::start()
{
    // clear the screen
    scene->clear();

    // test code
    hex_board = new HexBoard;
    hex_board->placeHexes(100, 100, 5, 5);

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
    setWhosTurn(QString("Player 1"));
    whos_turn_text->setPos(490,0);
    scene->addItem(whos_turn_text);
}

void Game::createNewCard(QString player)
{
     Hex * card = new Hex;
     card->setOwner(player);

     // add card to the list
     if (player == QString("PLAYER1"))
         player1_cards.append(card);
     else
         player2_cards.append(card);
}

void Game::createInitialCards()
{
    // player 1 cards
    for (size_t i = 0, n = 5; i < n; ++i) {
        createNewCard(QString("PLAYER1"));
    }

    // player 2 cards
    for (size_t i = 0, n = 5; i < n; ++i) {
        createNewCard(QString("PLAYER2"));
    }

    // draw cards
    drawCards();
}

void Game::drawCards()
{
    // remove player 1 cards
    for (size_t i = 0, n = player1_cards.size(); i < n; ++i) {
        scene->removeItem(player1_cards[i]);
    }

    // remove player 2 cards
    for (size_t i = 0, n = player2_cards.size(); i < n; ++i) {
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

QString Game::getWhosTurn()
{
    return whos_turn;
}

void Game::setWhosTurn(QString player)
{
    // change qstring
    whos_turn = player;

    // change text
    whos_turn_text->setPlainText(QString("Whos turn: ") + player);

}
