#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_draw.h>
#include <cmath>

class Being{
    protected:
        SDL_Rect        frame;          //hitbox и координаты
        SDL_Rect        prev_frame;
        SDL_Surface     *Surf;          //поверхность с моделькой
        SDL_Surface     *Prev_Surf;          //
        double          x;              //вещественные координаты (для более точного движения)
        double          y;
        struct {
            Uint16      speed;          //перемещение за кадр
            double      dx;             //перемещение по x
            double      dy;             //перемещение по y
        } speed;                        //скорость передвижаения;
        Sint16          health;         //здоровье
    public:
        Being();
        ~Being();
       void Set_Pos(Uint16 X, Uint16 Y, SDL_Surface*);
       void Set_Speed(Uint16 X, Uint16 Y);
       void Stop();
       void Move();
       void Draw(SDL_Surface*);
};

class Player: public Being{
    private:
        //статы, спеллы и прочее
        Sint16 intellect;
    public:
        Player();
        ~Player();
};
#endif // PLAYER_H
