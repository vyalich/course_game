#include "../header/Camera.h"

Camera Camera::CameraControl;

Camera::Camera() {
    X = Y = MaxX = MaxY = 0;
}

void Camera::OnMove(double MoveX, double MoveY) {
    if(MoveX >= 0 && MoveX+SCREEN_W <= MaxX)
        X = MoveX;
    if(MoveY >= 0 && MoveY+SCREEN_H <= MaxY)
        Y = MoveY;
}

int Camera::GetX() {
    return X;
}

int Camera::GetY() {
    return Y;
}

void Camera::OnInit(int X, int Y) {
    MaxX = MAP_W*TILE_SIZE;
    MaxY = MAP_H*TILE_SIZE;
    this->X = X;
    this->Y = Y;
}
