#ifndef HEX_BOARD_H
#define HEX_BOARD_H

#include "hex.h"

class HexBoard
{
public:
    HexBoard();

    // getters
    QList<Hex *> getHexes();

    // public methods
    void placeHexes();
private:
    void createHexColumn(int x, int y, int num_of_rows);
    QList<Hex *> hexes;

};

#endif // HEX_BOARD_H
