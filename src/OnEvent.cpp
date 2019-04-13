#include "../header/App.h"

void App::OnEvent(SDL_Event *event){
    if(event->type == SDL_QUIT){
        _running = false;
        _level = false;
    }
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_RIGHT){

            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_RIGHT){

            }
            break;
        /*case SDL_MOUSEMOTION:
            if(_mouse_key == 1){
                Hero.Set_Speed(event->motion.x, event->motion.y);
            }
            break;*/
        case SDL_KEYDOWN:
            OnKeyDown(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
    }
}

void App::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_UP:    Camera::CameraControl.OnMove( 0, -15); break;
        case SDLK_DOWN:  Camera::CameraControl.OnMove( 0,  15); break;
        case SDLK_LEFT:  Camera::CameraControl.OnMove(-15,  0); break;
        case SDLK_RIGHT: Camera::CameraControl.OnMove( 15,  0); break;
    }
}

