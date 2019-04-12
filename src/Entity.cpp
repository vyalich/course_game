#include "../header/Entity.h"

std::vector<CEntity*>     CEntity::EntityList;

std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() {
    EntityA = NULL;
    EntityB = NULL;
}

CEntity::CEntity() {
    Surf_Entity = NULL;

    X = 0;
    Y = 0;

    Width     = 0;
    Height     = 0;

    //MoveLeft  = false;
    //MoveRight = false;

    Type =     ENTITY_TYPE_GENERIC;

    //Dead = false;
    Flags = ENTITY_FLAG_GRAVITY;

    SpeedX = 0;
    SpeedY = 0;

    /*AccelX = 0;
    AccelY = 0;

    MaxSpeedX = 5;
    MaxSpeedY = 5;

    CurrentFrameCol = 0;
    CurrentFrameRow = 0;*/

    Col_X = 0;
    Col_Y = 0;

    Col_Width  = 0;
    Col_Height = 0;
}
