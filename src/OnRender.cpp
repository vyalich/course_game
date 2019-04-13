#include "../header/App.h"

void App::OnRender(){
    Map::MapControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    SDL_Flip(Surf_Display);
}
