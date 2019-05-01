#include "../header/GUI.h"

GUI GUI::GUIControl;

void GUI::OnInit(){
    ExpBar = {.x = 0, .y = SCREEN_H-8, .w = SCREEN_W, .h = 6, .cur = 0.7135436};
    HealthBar = {.x = SCREEN_W/5, .y = 5, .w = SCREEN_W/5*3, .h = 20, .cur = 1};
}

void GUI::OnLoop(){

}

void GUI::OnRender(SDL_Surface *Surf_Display){
    int dx = ExpBar.w/10;
    Draw_FillRect(Surf_Display, ExpBar.x, ExpBar.y, ExpBar.w, ExpBar.h, 0xd2f7a5);
    Draw_FillRect(Surf_Display, ExpBar.x, ExpBar.y, ExpBar.w*ExpBar.cur, ExpBar.h, 0x72ff00);
    for(int x = ExpBar.x; x < ExpBar.x+ExpBar.w; x += dx){
        Draw_Round(Surf_Display, x, ExpBar.y-1, dx, ExpBar.h+2, 2, 0x000000);
        Draw_Round(Surf_Display, x, ExpBar.y-2, dx, ExpBar.h+4, 3, 0x000000);
    }

}
