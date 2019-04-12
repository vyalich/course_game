#ifndef APP_H
#define APP_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_draw.h>
#include "Entity.h"
#include "Tile.h"

class App
{
    private:
        bool            _running;           //���� ���������� ����
        bool            _level;             //���� ���������� ������
        //char
        Sint8            _mouse_key;          //���� ������� ���
        SDL_Surface     *Surf_Display;       //����������� ������
        Player          Hero;


    public:
        App();
        ~App();
        int OnExecute();                //�������� ���� ����
        bool OnInit();                  //������������� ����
        void LevelInit();               //������������� ������
        void OnEvent(SDL_Event*);       //��������� �������
        void OnLoop();                  //������������ ��������
        void OnRender();                //��������� �����
        void LevelCleanup();            //������� ������
        void OnCleanup();               //������� ����
};

#endif // APP_H
