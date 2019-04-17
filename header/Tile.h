#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include "Define.h"

enum {
    TILE_TYPE_NORMAL = 0,
    TILE_TYPE_BLOCK
};

class Tile {
    public:
        int     TileID;
        int     TypeID;

    public:
        Tile();
};

#endif // TILE_H_INCLUDED
