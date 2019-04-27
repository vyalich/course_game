#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "Define.h"
using namespace std;

//проверка элемента
bool check(bool *element, int y, int x){
    int count = 0;

    for(int i = y-1; i < y+2; i++){
        for(int j = x-1; j < x+2; j++){
            if(i == y && j == x)
                continue;
            if(i < 0 || i >= MAP_H-1 || j < 0 || j >= MAP_W-1)
                count++;
            else if(element[i*MAP_W + j])
                count++;
        }
    }
    if(element[y*MAP_W + x]){
        if(count < DEADBOT || count > DEADTOP)
            return false;
        else
            return true;
    }
    else{
        if(count > BIRTH)
            return true;
    }
    return element[y*MAP_W + x];
}

//создание новой карты
bool* life_game(bool *MapOld){
    bool *MapNew = new bool[MAP_H*MAP_W];

    for(int i = 0; i < MAP_H; i++)
        for(int j = 0; j < MAP_W; j++)
            MapNew[i*MAP_W + j] = check(MapOld, i, j);
    delete MapOld;
    return MapNew;
}

int main()
{
    srand(time(0));
    FILE *MapFile;
    bool *Map = new bool[MAP_H*MAP_W];

    MapFile = fopen("1.map", "w");

    //заполнение карты рандомными клетками
    for(int i = 0; i < MAP_H; i++)
        for(int j = 0; j < MAP_W; j++)
            Map[i*MAP_W + j] = CHANCE;

    //вывод изначальной рандомной карты
    for(int i = 0; i < MAP_H; i++){
        for(int j = 0; j < MAP_W; j++)
            printf("%c ", (Map[i*MAP_W + j])? '#': '.');
        printf("\n");
    }
    printf("\n");

    char key = 0;
    while(key != 27){
        //создание новой карты
        Map = life_game(Map);
        //вывод новой карты
        for(int i = 0; i < MAP_H; i++){
            for(int j = 0; j < MAP_W; j++)
                printf("%c ", (Map[i*MAP_W + j])? '#': '.');
            printf("\n");
        }
        printf("\n");
        key = getch();
    }
    //запись карты в файл
    for(int i = 0; i < MAP_H; i++){
        for(int j = 0; j < MAP_W; j++){
                fprintf(MapFile, "%d:%d ", Map[i*MAP_W + j], Map[i*MAP_W + j]);
            }
        fprintf(MapFile, "\n");
    }
    fclose(MapFile);
    return 0;
}
