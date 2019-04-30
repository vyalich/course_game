#include "../header/Map.h"

Map Map::MapControl;

Map::Map() {
    Surf_Tileset = NULL;
}

bool Map::OnLoad(char* File) {
    TileList.clear();

    if((Surf_Tileset = Surface::OnLoad("./img/1.bmp")) == false) {
        return false;
    }

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL) {
        return false;
    }
    Tile tempTile;
    for(int Y = 0;Y < MAP_H;Y++) {
        for(int X = 0;X < MAP_W;X++) {
            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void Map::OnRender(SDL_Surface* Surf_Display, int CamX, int CamY) {
    if(Surf_Tileset == NULL) return;

    int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
    int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

    int FirstID = (int)CamX/TILE_SIZE + (int)CamY/TILE_SIZE*MAP_W;
    int MaxY = CamY + SCREEN_H;
    int MaxX = CamX + SCREEN_W;
    int ID;
    //отрисовка карты
    for(int MapY = FirstID/MAP_W*TILE_SIZE; MapY <= MaxY; MapY += TILE_SIZE) {
        ID = FirstID;
        for(int MapX = ID%MAP_W*TILE_SIZE; MapX <= MaxX; MapX += TILE_SIZE) {
            /*if(TileList[ID].TypeID == TILE_TYPE_NORMAL ) {
                ID++;
                continue;
            }*/
            //координаты тайла на экране
            int ScrX = MapX - CamX;
            int ScrY = MapY - CamY;
            //выбираем нужный тайл из тайлсета
            int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
            //отрисовка тайла
            Surface::OnDraw(Surf_Display, Surf_Tileset, ScrX, ScrY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

            ID++;
        }
        FirstID += MAP_W;
    }
}

void Map::OnCleanup() {
    if(Surf_Tileset) {
        SDL_FreeSurface(Surf_Tileset);
    TileList.clear();
    }
}

int Map::GetTileType(int ID){
    return TileList[ID].TypeID;
}
