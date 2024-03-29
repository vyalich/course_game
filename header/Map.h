#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL.h>
#include <vector>

#include "Tile.h"
#include "Surface.h"

class Map {
    public:
        static Map MapControl;

    public:
        SDL_Surface* Surf_Tileset;      //tileset

    private:
        std::vector<Tile> TileList;     //
        int          Tileset_w;
        int          Tileset_h;

    public:
        Map();

    public:
        bool OnLoad(char* File);

        void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);

        void OnCleanup();

        int GetTileType(int ID);
};

#endif // MAP_H_INCLUDED
