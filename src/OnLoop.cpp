#include "../header/App.h"

bool Compare(Entity *A, Entity *B){
    return A->MapY < B->MapY;
}

void App::OnLoop(){
    //Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.OnLoop(_mouse_left);

    double TarX = Hero.GetMapX();
    double TarY = Hero.GetMapY();
    int CamX = Camera::CameraControl.GetX();
    int CamY = Camera::CameraControl.GetY();
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnLoop(TarX, TarY, CamX, CamY, Surf_Display);

    Entity::OnScreen.sort(Compare);

    if(_mouse_right){
        Spell *temp = new Spell;
        temp->OnLoad();
        if(temp->CanCast())
            Spell::SpellCasted.insert(Spell::SpellCasted.end(), temp);
            //(*Spell::SpellCasted.end())->OnLoad();
        else
            delete temp;
    }
    /*for(auto iter = Spell::SpellCasted.begin(); iter != Spell::SpellCasted.end(); iter++){
        (*iter)->OnLoop();
    }*/

    GUI::GUIControl.OnLoop();
}
