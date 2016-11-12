#include "hex.h"
#include "player_type.h"
#include "game.h"

#include <QBrush>
#include <QGraphicsTextItem>

extern Game * game;

Hex::Hex(QGraphicsItem *parent)
{
    // draw
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2) << QPointF(1,2) << QPointF(0,1);

    int SCALE_BY = 40;

    for(size_t i = 0, n = hexPoints.size(); i < n; i++) {
        hexPoints[i] *= SCALE_BY;
    }

    // create polygon
    QPolygonF hexagon(hexPoints);

    // draw polygon
    setPolygon(hexagon);

    is_placed = false;

    // size attack
    side0_of_attack = 0;
    side1_of_attack = 0;
    side2_of_attack = 0;
    side3_of_attack = 0;
    side4_of_attack = 0;
    side5_of_attack = 0;

    // create QGraphicsTextItem for representside attack
    QGraphicsTextItem * text0 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem * text1 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem * text2 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem * text3 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem * text4 = new QGraphicsTextItem(QString::number(0),this);
    QGraphicsTextItem * text5 = new QGraphicsTextItem(QString::number(0),this);

    attack_texts.append(text0);
    attack_texts.append(text1);
    attack_texts.append(text2);
    attack_texts.append(text3);
    attack_texts.append(text4);
    attack_texts.append(text5);

    text0->setPos(50,0);
    text1->setPos(20,15);
    text2->setPos(20,40);
    text3->setPos(50,55);
    text4->setPos(80,40);
    text5->setPos(80,15);

    for (size_t i = 0, n = attack_texts.size(); i < n; i++) {
        attack_texts[i]->setVisible(false);
    }
}

bool Hex::getIsPlaced()
{
    return is_placed;
}

PlayerType Hex::getOwner()
{
    return owner;
}

void Hex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (getIsPlaced() == false) {
        game->pickUpCard(this);
    } else {
        game->placeCard(this);
    }
}

void Hex::setAttackOf(int size, int attack)
{
    switch (size) {
    case 0:
        side0_of_attack = attack;
        attack_texts[0]->setPlainText(QString::number(attack));
        break;
    case 1:
        side0_of_attack = attack;
        attack_texts[1]->setPlainText(QString::number(attack));
        break;
    case 2:
        side0_of_attack = attack;
        attack_texts[2]->setPlainText(QString::number(attack));
        break;
    case 3:
        side0_of_attack = attack;
        attack_texts[3]->setPlainText(QString::number(attack));
        break;
    case 4:
        side0_of_attack = attack;
        attack_texts[4]->setPlainText(QString::number(attack));
        break;
    case 5:
        side0_of_attack = attack;
        attack_texts[5]->setPlainText(QString::number(attack));
        break;
    default:
        break;
    }
}

void Hex::setOwner(PlayerType player)
{
    // set the owner
    owner = player;

    // change the color
    if (player == PlayerType::NONE) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::lightGray);
        setBrush(brush);
    } else if (player == PlayerType::PLAYER_ONE) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::blue);
        setBrush(brush);
    } else if (player == PlayerType::PLAYER_TWO) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}

void Hex::setIsPlaced(bool b)
{
    is_placed = b;
}

void Hex::displaySideAttack()
{
    for (size_t i = 0, n = attack_texts.size(); i < n; i++) {
        attack_texts[i]->setVisible(true);
    }
}
