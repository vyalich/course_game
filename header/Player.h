#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Entity.h"

class Player: public Entity{
    private:
        int intellect;
    public:
        Player();
        bool OnLoad(char* File, int Width, int Height);
};

#endif // PLAYER_H_INCLUDED
