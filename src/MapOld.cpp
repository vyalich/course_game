#include "../header/Map.h"

Map::Map() {
    Surf_Tileset = NULL;
}

bool Map::OnLoad(char* File) {
    TileList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL) {
        return false;
    }

    for(int Y = 0;Y < MAP_H;Y++) {
        for(int X = 0;X < MAP_W;X++) {
            Tile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

void Map::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
    if(Surf_Tileset == NULL) return;

    int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
    int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

    int ID = 0;
    //��������� �����
    for(int Y = 0;Y < MAP_H;Y++) {
        for(int X = 0;X < MAP_W;X++) {
            if(TileList[ID].TypeID == TILE_TYPE_NONE) {
                ID++;
                continue;
            }
            //���������� ����� �� �����
            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);
            //�������� ������ ���� �� ��������
            int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
            //��������� �����
            Surface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

            ID++;
        }
    }
}
