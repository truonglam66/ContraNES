#include "Map.h"
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "debug.h"

CMap::CMap(int TileSetID, int TotalRowsInMap, int TotalColumnsInMap, int RowsInTileSet, int ColumnsInTileSet, int TotalTiles, int** tileMatrix)
{
	TileTexture = CTextures::GetInstance()->Get(TileSetID);
	this->TotalRowsInMap = TotalRowsInMap;
	this->TotalColumnsInMap = TotalColumnsInMap;
	this->RowsInTileSet = RowsInTileSet;
	this->ColumnsInTileSet = ColumnsInTileSet;
	this->TotalTiles = TotalTiles;
	this->TileMap = tileMatrix;
}

CMap::~CMap()
{
}

void CMap::AddTiles()
{
	for (int tileID = 0; tileID < TotalTiles; tileID++)
	{
		int left = tileID % ColumnsInTileSet * TILE_WIDTH;
		int top = tileID / ColumnsInTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH - 1;
		int bottom = top + TILE_HEIGHT;
		//DebugOut(L"id, left, top, right, bottom: %d, %d, %d, %d, %d", tileID, left, top, right, bottom);
		LPSPRITE NewTile = new CSprite(tileID, left, top, right, bottom, TileTexture);
		this->Tiles.push_back(NewTile);
	}
}

void CMap::Render()
{
	int FirstColumn = int(floor(0 / TILE_WIDTH));
	int LastColumn = TotalColumnsInMap;
	if (LastColumn >= TotalColumnsInMap)
		LastColumn = TotalColumnsInMap - 1;
	int d = 0;
	for (int CurrentRow = 0; CurrentRow < TotalRowsInMap; CurrentRow++)
		for (int CurrentColumn = FirstColumn; CurrentColumn <= LastColumn; CurrentColumn++)
		{
			int index = TileMap[CurrentRow][CurrentColumn] - 1;
			if (index < TotalTiles)
			{
				float xDraw = float(CurrentColumn * TILE_WIDTH) + float(0 * TILE_WIDTH);
				float yDraw = float((this->TotalRowsInMap - CurrentRow) * TILE_HEIGHT) - float(0 * TILE_HEIGHT);
				Tiles.at(index)->Draw(xDraw - 9, yDraw - 1.0f);
			}
		}
}

int CMap::GetMapWidth()
{
	return TotalColumnsInMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	return TotalRowsInMap * TILE_HEIGHT;
}