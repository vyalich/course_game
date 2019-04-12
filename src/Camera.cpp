#include "../header/Camera.h"

Camera Camera::CameraControl;

Camera::Camera() {
    X = Y = 0;
}

void Camera::OnMove(double MoveX, double MoveY) {
    X += MoveX;
    Y += MoveY;
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
