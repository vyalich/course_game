#include "../header/App.h"

void App::LevelCleanup(){
    _level = false;
    for(int i = 0; i < ENEMIES; i++)
        Enemy::EnemyList[i]->OnCleanup();
    Enemy::EnemyList.clear();
}
