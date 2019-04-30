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
    int offset = MAP_H*MAP_W;
    int id = 0;
    int tileset_w = 6;
    //запись карты в файл
    for(int i = 0; i < MAP_H; i++){
        for(int j = 0; j < MAP_W; j++){
                if(Map[i*MAP_W + j]){
                    id = 1;

                    if(i > 0 && !Map[(i-1)*MAP_W + j])
                        id = 4;
                    if(i < MAP_H-1 && !Map[(i+1)*MAP_W + j])
                        id += 2;
                    if(i < MAP_H-2 && !Map[(i+2)*MAP_W + j] && Map[(i+1)*MAP_W + j])
                        id ++;
                    if(j > 0 && (!Map[i*MAP_W + j-1] || !Map[(i+1)*MAP_W + j-1] && i < MAP_H-1))
                        id += tileset_w;
                    if(j < MAP_W-1 && (!Map[i*MAP_W + j+1] || !Map[(i+1)*MAP_W + j+1] && i < MAP_H-1))
                        id += 2*tileset_w;
                    fprintf(MapFile, "%d:1 ", id);
                }
                else{
                    id = 0;
                    fprintf(MapFile, "%d:0 ", id);
                }
            }
        fprintf(MapFile, "\n");
    }
    fclose(MapFile);
    return 0;
}
