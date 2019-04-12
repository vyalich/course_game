#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_draw.h>
#include <cmath>

class Being{
    protected:
        SDL_Rect        frame;          //hitbox � ����������
        SDL_Rect        prev_frame;
        SDL_Surface     *Surf;          //����������� � ���������
        SDL_Surface     *Prev_Surf;          //
        double          x;              //������������ ���������� (��� ����� ������� ��������)
        double          y;
        struct {
            Uint16      speed;          //����������� �� ����
            double      dx;             //����������� �� x
            double      dy;             //����������� �� y
        } speed;                        //�������� �������������;
        Sint16          health;         //��������
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
        //�����, ������ � ������
        Sint16 intellect;
    public:
        Player();
        ~Player();
};
#endif // PLAYER_H
