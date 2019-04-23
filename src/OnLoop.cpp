#include "../header/App.h"

void App::OnLoop(){
    Hero.OnLoop();

    double TarX = Hero.GetMapX();
    double TarY = Hero.GetMapY();
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnLoop(TarX, TarY);
}
