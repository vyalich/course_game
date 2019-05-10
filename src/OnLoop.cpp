#include "../header/App.h"

bool Compare(Entity *A, Entity *B){
    return A->MapY < B->MapY;
}

void App::OnLoop(){
    //Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.OnLoop(_mouse_left, Inter);

    double TarX = Hero.GetMapX();
    double TarY = Hero.GetMapY();
    int CamX = Camera::CameraControl.GetX();
    int CamY = Camera::CameraControl.GetY();
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnLoop(TarX, TarY, CamX, CamY, Surf_Display, Inter);

    if(_mouse_right)
        Spell::AddCasted();

    for(auto spell : Spell::SpellCasted){
        spell->OnLoop();
    }

    Entity::OnScreen.sort(Compare);


    GUI::GUIControl.OnLoop();
}
