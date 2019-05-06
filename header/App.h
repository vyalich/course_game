#ifndef APP_H
#define APP_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_draw.h>
#include <ctime>
#include <cstdlib>
#include "Entity.h"
#include "Player.h"
#include "Define.h"
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "GUI.h"
#include "Spell.h"

class Player;

class App
{
    private:
        bool            _running;           //���� ���������� ����
        bool            _level;             //���� ���������� ������
        //char
        bool            _mouse_left;          //���� ������� ���
        bool            _mouse_right;
        double          Inter;
        Uint32          start;
        Uint32          loops;
        Uint16          fps;
        SDL_Surface     *Surf_Display;       //����������� ������
        SDL_Rect        ClipForDraw;

    public:
        static Player   Hero;
        static SDL_Surface  *ForDraw;


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
        void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
};

#endif // APP_H
