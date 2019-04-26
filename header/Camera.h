#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <SDL.h>

#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};

class Camera {
    public:
        static Camera CameraControl;

    private:
        int X;
        int Y;
        int MaxX;
        int MaxY;

    public:
        Camera();

    public:
        void OnMove(double MoveX, double MoveY);

    public:
        int GetX();
        int GetY();

    public:
        void OnInit(int X, int Y);
};

#endif // CAMERA_H_INCLUDED
