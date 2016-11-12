#ifndef HEX_H
#define HEX_H

#include "player_type.h"

#include <QGraphicsPolygonItem>

class Hex : public QGraphicsPolygonItem
{
public:
    Hex(QGraphicsItem * parent=0);

    // getters
    int getAttackOf(int size);
    bool isPlaced();
    PlayerType getOwner();

    // setters
    void setAttackOf(int size, int attack);
    void setOwner(PlayerType player);
    void setIsPlaced(bool b);
private:
    bool is_placed;
    PlayerType owner;
    int side1_of_attack;
    int side2_of_attack;
    int side3_of_attack;
    int side4_of_attack;
    int side5_of_attack;
};

#endif // HEX_H
