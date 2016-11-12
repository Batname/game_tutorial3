#ifndef HEX_H
#define HEX_H

#include "player_type.h"

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Hex : public QGraphicsPolygonItem
{
public:
    Hex(QGraphicsItem * parent=0);

    // getters
    int getAttackOf(int size);
    bool getIsPlaced();
    PlayerType getOwner();

    // events
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    // setters
    void setAttackOf(int size, int attack);
    void setOwner(PlayerType player);
    void setIsPlaced(bool b);

    // member function
    void displaySideAttack();

private:
    bool is_placed;
    PlayerType owner;
    int side0_of_attack;
    int side1_of_attack;
    int side2_of_attack;
    int side3_of_attack;
    int side4_of_attack;
    int side5_of_attack;
    QList<QGraphicsTextItem *> attack_texts;
};

#endif // HEX_H
