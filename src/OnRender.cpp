#include "../header/App.h"

void App::OnRender(){
    Area::AreaControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
    Hero.Draw(Surf_Display);
    SDL_Flip(Surf_Display);
}
