#include "../header/Camera.h"

Camera Camera::CameraControl;

Camera::Camera() {
    X = Y = 0;
}

void Camera::OnMove(double MoveX, double MoveY) {
    X += MoveX;
    if (X < 0 || X + SCREEN_W > MAP_W*TILE_SIZE)
        X -= MoveX;
    Y += MoveY;
    if (Y < 0 || Y + SCREEN_H> MAP_H*TILE_SIZE)
        Y -= MoveY;
}

int Camera::GetX() {
    return X;
}

int Camera::GetY() {
    return Y;
}

void Camera::SetPos(int X, int Y) {
    this->X = X;
    this->Y = Y;
}
