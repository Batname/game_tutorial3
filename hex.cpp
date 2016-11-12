#include "hex.h"
#include "player_type.h"
#include "game.h"

#include <QBrush>
#include <QGraphicsTextItem>
#include <QLineF>
#include <QDebug>

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

    createLines();

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

int Hex::getAttackOf(int side){
    if (side == 0){
        return side0_of_attack;
    }
    else if (side == 1){
        return side1_of_attack;
    }
    else if (side == 2){
        return side2_of_attack;
    }
    else if (side == 3){
        return side3_of_attack;
    }
    else if (side == 4){
        return side4_of_attack;
    }
    else if (side == 5){
        return side5_of_attack;
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

void Hex::setAttackOf(int side, int attack)
{
    switch (side) {
    case 0:
        side0_of_attack = attack;
        attack_texts[0]->setPlainText(QString::number(attack));
    case 1:
        side1_of_attack = attack;
        attack_texts[1]->setPlainText(QString::number(attack));
    case 2:
        side2_of_attack = attack;
        attack_texts[2]->setPlainText(QString::number(attack));
    case 3:
        side3_of_attack = attack;
        attack_texts[3]->setPlainText(QString::number(attack));
    case 4:
        side4_of_attack = attack;
        attack_texts[4]->setPlainText(QString::number(attack));
    case 5:
        side5_of_attack = attack;
        attack_texts[5]->setPlainText(QString::number(attack));
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

void Hex::createLines()
{
    QPointF hex_center(x()+60, y()+40);
    QPointF final_pt(hex_center.x(), hex_center.y() - 65);
    QLineF ln(hex_center, final_pt);

    for (size_t i = 0, n = 6; i < n; i++) {
       QLineF ln_copy(ln);
       ln_copy.setAngle(90+60 * i);
       QGraphicsLineItem * line = new QGraphicsLineItem(ln_copy, this);
       lines.append(line);
       line->setVisible(false);
    }
}

void Hex::findNeighbors()
{
    for (size_t i = 0, n = lines.size(); i < n; i++) {
        // check if that collides and add to Neighbors
        QList<QGraphicsItem *> c_items = lines[i]->collidingItems();
        for (size_t j = 0, m = c_items.size(); j < m; j++) {
            Hex * item = dynamic_cast<Hex *>(c_items[j]);
            if (c_items[j] != this && item) {
                neighbors.append(item);
            }
        }
    }
}

void Hex::switchOwner()
{
    if (getOwner() == PlayerType::PLAYER_ONE) {
        setOwner(PlayerType::PLAYER_TWO);
    } else if (getOwner() == PlayerType::PLAYER_TWO) {
        setOwner(PlayerType::PLAYER_ONE );
    }
}

void Hex::captureNaighbors()
{
    for (size_t i = 0, n = neighbors.size(); i < n; i++) {
        bool is_enamy = false;
        bool is_not_neutral = false;
        if (this->getOwner() != neighbors[i]->getOwner()) {
            is_enamy = true;
        }

        if (neighbors[i]->getOwner()  != PlayerType::NONE) {
            is_not_neutral = true;
        }

        if (is_enamy && is_not_neutral) {
            int this_attack = 0;
            int neighbor_attack = 0;
            if (i == 0) {
                this_attack = getAttackOf(0);
                neighbor_attack = neighbors[0]->getAttackOf(3);
            } else if (i == 1) {
                this_attack = getAttackOf(1);
                neighbor_attack = neighbors[1]->getAttackOf(4);
            } else if (i == 2) {
                this_attack = getAttackOf(2);
                neighbor_attack = neighbors[2]->getAttackOf(5);
            } else if (i == 3) {
                this_attack = getAttackOf(3);
                neighbor_attack = neighbors[3]->getAttackOf(0);
            } else if (i == 4) {
                this_attack = getAttackOf(4);
                neighbor_attack = neighbors[4]->getAttackOf(1);
            } else if (i == 5) {
                this_attack = getAttackOf(5);
                neighbor_attack = neighbors[5]->getAttackOf(2);
            }

            if (this_attack > neighbor_attack) {
                neighbors[i]->switchOwner();
            }
        }
    }
}
