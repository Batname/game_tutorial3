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
