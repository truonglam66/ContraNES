/*
#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Bill.h"
#include "QuadTree.h"


class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	LPTREENODE QuadTree;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void AddObject(LPGAMEOBJECT object);


	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void Clear();
	virtual void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	virtual void AddObjectToQuadTree(LPGAMEOBJECT obj) { QuadTree->AddObject(obj); }

	//virtual void DeleteObject(LPGAMEOBJECT object) {};
	//virtual void AddObjectInGame(LPGAMEOBJECT object) {};


	LPGAMEOBJECT GetPlayer() { return player; }


};

typedef CPlayScene* LPPLAYSCENE;
*/

#pragma once
#include "Scene.h"
//#include "Map.h"
#include "QuadTree.h"
#define CAM_CHANGE_TIME		30

class CBullet;
class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	//CMap* current_map = NULL;
	vector<LPGAMEOBJECT> objects;
	LPTREENODE QuadTree;
	vector<CBullet*>* ammo;

	float camL = 0, camT = 0, camR = 0, camB = 0;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_TILEMAP_DATA(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void AddObject(LPGAMEOBJECT object);

	//vector<LPGAMEOBJECT> GetListObject() { return objects; }
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	//CMap* GetMap() { return current_map; }
	virtual void Clear();
	virtual void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	virtual void AddObjectToQuadTree(LPGAMEOBJECT obj) { QuadTree->AddObject(obj); }

	virtual void DeleteObject(LPGAMEOBJECT object) {};
	virtual void AddObjectInGame(LPGAMEOBJECT object) {};

	vector<CBullet*>* GetAmmo() { return ammo; }
	LPGAMEOBJECT GetPlayer() { return player; }
};

typedef CPlayScene* LPPLAYSCENE;

