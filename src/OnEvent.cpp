#include "../header/App.h"

void App::OnEvent(SDL_Event *event){
    if(event->type == SDL_QUIT){
        _running = false;
        _level = false;
    }
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            if(event->button.button == SDL_BUTTON_LEFT){
                _mouse_left = true;
            }
            if(event->button.button == SDL_BUTTON_RIGHT){
                _mouse_right = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_LEFT){
                _mouse_left = false;
            }
            if(event->button.button == SDL_BUTTON_RIGHT){
                _mouse_right = false;
            }
            break;

        case SDL_KEYDOWN:
            if(event->key.keysym.sym == SDLK_ESCAPE){
                _running = false;
                _level = false;
            }

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

