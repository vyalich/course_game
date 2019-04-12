#ifndef AREA_H_INCLUDED
#define AREA_H_INCLUDED

#include "Map.h"

class Area {
    public:
        static Area            AreaControl;

    public:
        std::vector<Map>       MapList;

    private:
        int                     AreaSize;

        SDL_Surface*        Surf_Tileset;

    public:
        Area();

        bool    OnLoad(char* File);

        void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);

        void    OnCleanup();
};

#endif // AREA_H_INCLUDED
