#include "../header/Entity.h"
Being::Being(){
    health = 10;
    speed.speed = 5;
    speed.dx = 0;
    speed.dy = 0;
    prev_frame.w = frame.w = 20;
    prev_frame.h = frame.h = 20;
    Surf = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, frame.w, frame.h, 32, 0, 0, 0, 0);
    Prev_Surf = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF, frame.w, frame.h, 32, 0, 0, 0, 0);
}

void Being::Set_Pos(Uint16 X, Uint16 Y, SDL_Surface *Surf_Display){   //установка начальной позиции
    x = prev_frame.x = frame.x = X;
    y = prev_frame.y = frame.y = Y;
    SDL_BlitSurface(Surf_Display, &frame, Prev_Surf, 0);
}

void Being::Set_Speed(Uint16 X, Uint16 Y){  //расчет новых значений скорости
        X -= 10;
        Y -= 10;
        double a = atan2(X-frame.x, Y-frame.y);
        speed.dx = speed.speed*sin(a);
        speed.dy = speed.speed*cos(a);
}

void Being::Stop(){
    speed.dx = speed.dy = 0;
}

void Being::Move(){     //передвижение объект в новую позицию
    x += speed.dx;
    y += speed.dy;
    frame.x = x;
    frame.y = y;
}

void Being::Draw(SDL_Surface *Surf_Display){    //отрисовка объекта
    SDL_BlitSurface(Prev_Surf, 0, Surf_Display, &prev_frame);
    SDL_BlitSurface(Surf_Display, &frame, Prev_Surf, 0);
    SDL_BlitSurface(Surf, 0, Surf_Display, &frame);
    prev_frame.x = frame.x;
    prev_frame.y = frame.y;
}

Being::~Being(){
    SDL_FreeSurface(Surf);
}

Player::Player(): Being(){
    intellect = 10;
    Draw_FillRect(Surf, 0, 0, frame.w, frame.h, 0x000000);
    Draw_FillRect(Surf, 1, 1, frame.w-2, frame.h-2, 0x0000ff);
}

Player::~Player(){
    SDL_FreeSurface(Surf);
    SDL_FreeSurface(Prev_Surf);
}
