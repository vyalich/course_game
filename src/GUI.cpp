#include "../header/GUI.h"

GUI GUI::GUIControl;

void Bar::Draw(SDL_Surface *Surf_Display){
    if(reversed)
        Draw_FillRect(Surf_Display, x+w*(1-cur), y+5, w*cur, h-10, Color);
    else
        Draw_FillRect(Surf_Display, x, y+5, w*cur, h-10, Color);
    for(int i = 0; i < 3; i++)
        Draw_Round(Surf_Display, x+i, y+i, w-i*2, h-i*2, 5-i, 0x000000);
    for(int i = 2; i < 5; i++)
        Draw_Rect(Surf_Display, x+i, y+i, w-i*2, h-i*2, 0x000000);

}

/*void Bar::Draw(SDL_Surface *Surf_Display){
    Draw_FillRound(Surf_Display, x, y, w*cur, h, 2, 0xff0000);
    Draw_Round(Surf_Display, x, y, w, h, 2, 0x000000);
    Draw_Rect(Surf_Display, x+1, y+1, w-2, h-2, 0x000000);
}*/
void Bar::RenderText(SDL_Surface *Surf_Display, TTF_Font *Font, int MarginTop){
    SDL_Surface *message;


    message = TTF_RenderText_Blended( Font, info.c_str(), TextColor );
    SDL_Rect dest = {.x = x+w/2-message->w/2, .y = y+MarginTop};
    if(message){
        SDL_BlitSurface(message, 0, Surf_Display, &dest);
        SDL_FreeSurface(message);
        message = NULL;
    }
}

void GUI::OnInit(){
    Font16 = TTF_OpenFont("CharisSILR.ttf", 16);
    Font12 = TTF_OpenFont("CharisSILR.ttf", 12);

    std::ifstream in("./misc/Bars.bin");

    if(!in)
        return;

    unsigned int n = 0;
    double d = 0;
    SDL_Surface *Temp;

    for(int i = 0; i < 4; i++){
        in >> n;   BarList[i].x = n;
        in >> n;   BarList[i].y = n;
        in >> n;   BarList[i].w = n;
        in >> n;   BarList[i].h = n;
        in >> d;   BarList[i].cur = d;
        in >> n;   BarList[i].Color = n;
        in >> n;   BarList[i].TextColor.r = n;
        in >> n;   BarList[i].TextColor.g = n;
        in >> n;   BarList[i].TextColor.b = n;

        Temp = SDL_CreateRGBSurface(SDL_HWSURFACE, BarList[i].w, BarList[i].h, 32, 0, 0, 0, 0);
        Surface::Transparent(Temp, 255, 0, 255);
        SDL_SetAlpha(Temp, SDL_SRCALPHA | SDL_RLEACCEL, 0x70);
        BarList[i].Background = SDL_DisplayFormat(Temp);
        SDL_FreeSurface(Temp);
        Draw_FillRect(BarList[i].Background, 0, 0, BarList[i].w, BarList[i].h, 0xff00ff);
        Draw_FillRect(BarList[i].Background, 5, 5, BarList[i].w-10, BarList[i].h-10, BarList[i].Color);
    }
    in.close();
    Draw_FillRect(BarList[EXP].Background, 0, 0, BarList[EXP].w, BarList[EXP].h, BarList[EXP].Color);
    BarList[HEALTH].reversed = true;
}

void GUI::OnLoop(){
    BarList[HEALTH].cur = App::Hero.Health/App::Hero.MaxHealth;

    BarList[MANA].cur = App::Hero.Mana/App::Hero.MaxMana;


}

void GUI::OnRender(SDL_Surface *Surf_Display){
    DrawBars(Surf_Display);
}

void GUI::DrawBars(SDL_Surface *Surf_Display){
    for(int i = 0; i < 3; i++){
        SDL_Rect coords = {.x = BarList[i].x, .y = BarList[i].y, .w = BarList[i].w, .h = BarList[i].h};
        SDL_BlitSurface(BarList[i].Background, 0, Surf_Display, &coords);

    }

    BarList[HEALTH].Draw(Surf_Display);
    BarList[MANA].Draw(Surf_Display);

    Draw_FillRect(Surf_Display, BarList[EXP].x, BarList[EXP].y, BarList[EXP].w*BarList[EXP].cur, BarList[EXP].h, BarList[EXP].Color);
    int dx = SCREEN_W/10;
    for(int x = 0; x < SCREEN_W-1; x += dx){
        Draw_Round(Surf_Display, x, SCREEN_H-10, dx, 8, 2, 0x000000);
        Draw_Round(Surf_Display, x, SCREEN_H-11, dx, 10, 3, 0x000000);
    }

    for(int i = 0; i < ENEMIES; i++){
        if(Enemy::EnemyList[i]->_mouseover){
            BarList[ENEMY].cur = Enemy::EnemyList[i]->Health/Enemy::EnemyList[i]->MaxHealth;
            BarList[ENEMY].info = std::to_string((int)Enemy::EnemyList[i]->Health) + " / " + std::to_string(Enemy::EnemyList[i]->MaxHealth);
            SDL_Rect coords = {.x = BarList[ENEMY].x, .y = BarList[ENEMY].y, .w = BarList[ENEMY].w, .h = BarList[ENEMY].h};
            SDL_BlitSurface(BarList[ENEMY].Background, 0, Surf_Display, &coords);
            BarList[ENEMY].Draw(Surf_Display);
            BarList[ENEMY].RenderText(Surf_Display, Font16, -1);
            break;
        }
    }

    BarList[HEALTH].info = std::to_string((int)App::Hero.Health) + " / " + std::to_string(App::Hero.MaxHealth);
    BarList[HEALTH].RenderText(Surf_Display, Font16, 1);
    BarList[MANA].info = std::to_string((int)App::Hero.Mana) + " / " + std::to_string(App::Hero.MaxMana);
    BarList[MANA].RenderText(Surf_Display, Font16, 1);

}

void GUI::OnCleanup(){
    TTF_CloseFont(Font12);
    TTF_CloseFont(Font16);

    for(int i = 0; i < 4; i++){
        SDL_FreeSurface(BarList[i].Background);
    }
}
