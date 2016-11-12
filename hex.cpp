#include "hex.h"
#include "player_type.h"

#include <QBrush>

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
}

PlayerType Hex::getOwner()
{
    return owner;
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
