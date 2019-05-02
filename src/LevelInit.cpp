#include "../header/App.h"

void App::LevelInit(){
    _level = true;
    Enemy *temp;
    for(int i = 0; i < ENEMIES; i++){
        temp= new Enemy;
        Enemy::EnemyList.push_back(temp);
        Enemy::EnemyList[i]->OnLoad(3);
    }
}
