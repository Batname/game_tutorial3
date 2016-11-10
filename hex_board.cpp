#include "hex_board.h"
#include "hex.h"
#include "game.h"

extern Game * game;

HexBoard::HexBoard()
{

}

QList<Hex *> HexBoard::getHexes()
{
    return hexes;
}

void HexBoard::placeHexes()
{
    createHexColumn(100, 100, 5);
}

void HexBoard::createHexColumn(int x, int y, int num_of_rows)
{
    // create column of hexes
    for(size_t i = 0, n = num_of_rows; i < n; ++i) {
        Hex * hex = new Hex;
        hex->setPos(x, y+82*i);
        hexes.append(hex);
        game->scene->addItem(hex);
    }
}
