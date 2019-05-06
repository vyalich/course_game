#include "../header/App.h"

void App::OnLoop(){
    //Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.OnLoop(_mouse_left);

    double TarX = Hero.GetMapX();
    double TarY = Hero.GetMapY();
    int CamX = Camera::CameraControl.GetX();
    int CamY = Camera::CameraControl.GetY();
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnLoop(TarX, TarY, CamX, CamY, Surf_Display);

    if(_mouse_right){
        Spell *temp = new Spell;
        if(temp->CanCast()){
            temp->OnLoad();
            Spell::SpellCasted.push_back(temp);
        }
        else
            delete temp;
    }
    for(auto iter = Spell::SpellCasted.begin(); iter != Spell::SpellCasted.end(); iter++){
        (*iter)->OnLoop();
    }

    GUI::GUIControl.OnLoop();
}
