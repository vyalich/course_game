#include "../header/App.h"

void App::OnLoop(){
    //Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.OnLoop();

    double TarX = Hero.GetMapX();
    double TarY = Hero.GetMapY();
    int CamX = Camera::CameraControl.GetX();
    int CamY = Camera::CameraControl.GetY();
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnLoop(TarX, TarY, CamX, CamY, Surf_Display);

    GUI::GUIControl.OnLoop();
}
