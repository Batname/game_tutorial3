#include "hex_board.h"
#include "hex.h"
#include "game.h"
#include "player_type.h"

extern Game * game;

HexBoard::HexBoard()
{

}

QList<Hex *> HexBoard::getHexes()
{
    return hexes;
}

void HexBoard::placeHexes(int x, int y, int num_of_columns, int num_of_rows)
{
    int X_SHIFT = 82;
    int Y_SHIFT = 41;

    for (size_t i = 0, n = num_of_columns; i < n; ++i) {
        if (i % 2 == 0) createHexColumn(x+X_SHIFT*i, y, num_of_rows);
        else createHexColumn(x+X_SHIFT*i, y+Y_SHIFT, num_of_rows);
    }
}

void HexBoard::createHexColumn(int x, int y, int num_of_rows)
{
    int Y_SHIFT = 82;
    // create column of hexes
    for(size_t i = 0, n = num_of_rows; i < n; ++i) {
        Hex * hex = new Hex;
        hex->setPos(x, y+Y_SHIFT*i);
        hexes.append(hex);
        game->scene->addItem(hex);

        // set owner to NODE initially
        hex->setOwner(PlayerType::NONE);
        hex->setIsPlaced(true);
    }
}
