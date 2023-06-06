//
//#include <iostream>
//#include <fstream>
//
//#include "PlayScene.h"
//#include "Utils.h"
//#include "Textures.h"
//#include "Sprites.h"
//#include "AssetIDs.h"
//#include "Soldier.h"
//#include "Bill.h"
//#include "Portal.h"
//
//
//
//#include "SampleKeyEventHandler.h"
//#include "debug.h"
//#include <unordered_set>
//
//using namespace std;
//
//CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
//	CScene(id, filePath)
//{
//	player = NULL;
//	key_handler = new CSampleKeyHandler(this);
//}
//
//
//#define SCENE_SECTION_UNKNOWN -1
//#define SCENE_SECTION_ASSETS	1
//#define SCENE_SECTION_OBJECTS	2
//
//#define ASSETS_SECTION_UNKNOWN -1
//#define ASSETS_SECTION_SPRITES 1
//#define ASSETS_SECTION_ANIMATIONS 2
//
//#define MAX_SCENE_LINE 1024
//
//void CPlayScene::_ParseSection_SPRITES(string line)
//{
//	vector<string> tokens = split(line);
//
//	if (tokens.size() < 6) return; // skip invalid lines
//
//	int ID = atoi(tokens[0].c_str());
//	int l = atoi(tokens[1].c_str());
//	int t = atoi(tokens[2].c_str());
//	int r = atoi(tokens[3].c_str());
//	int b = atoi(tokens[4].c_str());
//	int texID = atoi(tokens[5].c_str());
//
//	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
//	if (tex == NULL)
//	{
//		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
//		return;
//	}
//
//	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
//}
//
//void CPlayScene::_ParseSection_ASSETS(string line)
//{
//	vector<string> tokens = split(line);
//
//	if (tokens.size() < 1) return;
//
//	wstring path = ToWSTR(tokens[0]);
//
//	LoadAssets(path.c_str());
//}
//
//void CPlayScene::_ParseSection_ANIMATIONS(string line)
//{
//	vector<string> tokens = split(line);
//
//	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time
//
//	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());
//
//	LPANIMATION ani = new CAnimation();
//
//	int ani_id = atoi(tokens[0].c_str());
//	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
//	{
//		int sprite_id = atoi(tokens[i].c_str());
//		int frame_time = atoi(tokens[i + 1].c_str());
//		ani->Add(sprite_id, frame_time);
//	}
//
//	CAnimations::GetInstance()->Add(ani_id, ani);
//}
//
///*
//	Parse a line in section [OBJECTS]
//*/
//void CPlayScene::_ParseSection_OBJECTS(string line)
//{
//	vector<string> tokens = split(line);
//
//	// skip invalid lines - an object set must have at least id, x, y
//	if (tokens.size() < 2) return;
//
//	int object_type = atoi(tokens[0].c_str());
//	float x = (float)atof(tokens[1].c_str());
//	float y = (float)atof(tokens[2].c_str());
//
//	CGameObject* obj = NULL;
//
//	switch (object_type)
//	{
//	case OBJECT_TYPE_BILL:
//		if (player != NULL)
//		{
//			return;
//		}
//		obj = new CBill(x, y);
//		player = (CBill*)obj;
//		break;
//	//case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
//	//case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
//	//case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
//
//	/*case OBJECT_TYPE_PLATFORM:
//	{
//
//		float cell_width = (float)atof(tokens[3].c_str());
//		float cell_height = (float)atof(tokens[4].c_str());
//		int length = atoi(tokens[5].c_str());
//		int sprite_begin = atoi(tokens[6].c_str());
//		int sprite_middle = atoi(tokens[7].c_str());
//		int sprite_end = atoi(tokens[8].c_str());
//
//		obj = new CPlatform(
//			x, y,
//			cell_width, cell_height, length,
//			sprite_begin, sprite_middle, sprite_end
//		);
//
//		break;
//	}*/
//
//	//case OBJECT_TYPE_PORTAL:
//	//{
//	//	float r = (float)atof(tokens[3].c_str());
//	//	float b = (float)atof(tokens[4].c_str());
//	//	int scene_id = atoi(tokens[5].c_str());
//	//	obj = new CPortal(x, y, r, b, scene_id);
//	//}
//	//break;
//
//	case OBJECT_TYPE_SOLDIER:
//	{
//		obj = new CSoldier(x, y);
//		break;
//	}
//	break;
//
//	default:
//		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
//		return;
//	}
//
//	// General object setup
//	obj->SetPosition(x, y);
//
//	if (!dynamic_cast<CBill*>(obj))
//		QuadTree->AddObject(obj);
//
//	objects.push_back(obj);
//}
//
//void CPlayScene::LoadAssets(LPCWSTR assetFile)
//{
//	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);
//
//	ifstream f;
//	f.open(assetFile);
//
//	int section = ASSETS_SECTION_UNKNOWN;
//
//	char str[MAX_SCENE_LINE];
//	while (f.getline(str, MAX_SCENE_LINE))
//	{
//		string line(str);
//
//		if (line[0] == '#') continue;	// skip comment lines	
//
//		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
//		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
//		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
//
//		//
//		// data section
//		//
//		switch (section)
//		{
//		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
//		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
//		}
//	}
//
//	f.close();
//
//	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
//}
//
//void CPlayScene::Load()
//{
//	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
//
//	ifstream f;
//	f.open(sceneFilePath);
//
//	// current resource section flag
//	int section = SCENE_SECTION_UNKNOWN;
//
//	char str[MAX_SCENE_LINE];
//	while (f.getline(str, MAX_SCENE_LINE))
//	{
//		string line(str);
//
//		if (line[0] == '#') continue;	// skip comment lines	
//		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
//		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
//		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
//
//		//
//		// data section
//		//
//		switch (section)
//		{
//		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
//		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
//		}
//	}
//
//	f.close();
//
//	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
//}
//
///*void CPlayScene::Update(DWORD dt)
//{
//	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
//	// TO-DO: This is a "dirty" way, need a more organized way 
//
//	vector<LPGAMEOBJECT> coObjects;
//	for (size_t i = 1; i < objects.size(); i++)
//	{
//		coObjects.push_back(objects[i]);
//	}
//
//	for (size_t i = 0; i < objects.size(); i++)
//	{
//		objects[i]->Update(dt, &coObjects);
//	}
//
//	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
//	if (player == NULL) return;
//
//	// Update camera to follow mario
//	float cx, cy;
//	player->GetPosition(cx, cy);
//
//	CGame* game = CGame::GetInstance();
//	cx -= game->GetBackBufferWidth() / 2;
//	cy -= game->GetBackBufferHeight() / 2;
//
//	if (cx < 0) cx = 0;
//
//	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/
//
//	//PurgeDeletedObjects();
////} 
//
//void CPlayScene::Update(DWORD dt)
//{
//	unordered_set<LPGAMEOBJECT> coObjects;
//	vector<LPTREENODE>* treeNodeList = QuadTree->NodeInCam();
//	for (int i = 0; i < treeNodeList->size(); i++)
//	{
//		vector<LPGAMEOBJECT>* gameObjectsList = treeNodeList->at(i)->GetObject();
//		if (gameObjectsList != NULL)
//		{
//			for (int i = 0; i < gameObjectsList->size(); i++)
//				coObjects.insert(gameObjectsList->at(i));
//		}
//	}
//	vector<LPGAMEOBJECT> object;
//	object.insert(object.end(), coObjects.begin(), coObjects.end());
//	for (size_t i = 0; i < object.size(); i++)
//	{
//		object.at(i)->Update(dt, &object);
//		QuadTree->Update(object.at(i));
//	}
//	player->Update(dt, &object);
//	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
//	if (player == NULL) return;
//
//	// Update camera to follow marioD
//	float cx, cy;
//	player->GetPosition(cx, cy);
//	//for (int i = 0; i < ammo->size(); i++)
//	//	ammo->at(i)->Update(dt, &object);
//	CGame* game = CGame::GetInstance();
//	cx -= game->GetBackBufferWidth() / 2;
//	cy = 0;
//	if (cx < 0) cx = 0;
//	//if (cx > FULL_WEIGHT_1_1 - ADJUST_CAMERA_X) cx = FULL_WEIGHT_1_1 - ADJUST_CAMERA_X;
//
//
//	//if (cy > ADJUST_CAM_MAX_Y) cy = ADJUST_CAM_MAX_Y;
//	//else if ((ADJUST_CAM_MIN_Y < cy) && (cy < ADJUST_CAM_MAX_Y)) cy = ADJUST_CAM_MAX_Y;
//	//else  cy = ADJUST_CAM_MAX_Y + cy - ADJUST_CAM_MIN_Y;
//	//else if (cy < ADJUST_CAM_MAX_Y) cy =  cy+ ADJUST_CAM_MAX_Y ;
//	if (cy < 0) cy = 0;
//
//	CGame::GetInstance()->SetCamPos(cx, cy);
//
//
//	PurgeDeletedObjects();
//}
//
///*void CPlayScene::Render()
//{
//	for (int i = 0; i < objects.size(); i++)
//		objects[i]->Render();
//}*/
//
//void CPlayScene::Render()
//{
//	CGame* game = CGame::GetInstance();
//
//	//current_map->Render();
//
//	unordered_set<LPGAMEOBJECT> coObjects;
//	vector<LPTREENODE>* treeNodeList = QuadTree->NodeInCam();
//	for (int i = 0; i < treeNodeList->size(); i++)
//	{
//		vector<LPGAMEOBJECT>* gameObjectsList = treeNodeList->at(i)->GetObject();
//		if (gameObjectsList != NULL)
//		{
//			for (int i = 0; i < gameObjectsList->size(); i++)
//				coObjects.insert(gameObjectsList->at(i));
//		}
//	}
//	for (auto i = coObjects.begin(); i != coObjects.end(); ++i)
//		(*i)->Render();
//	//for (auto i = ammo->begin(); i != ammo->end(); ++i)
//	//	(i)->Render();
//	player->Render();
//}
//
///*
//*	Clear all objects from this scene
//*/
//void CPlayScene::Clear()
//{
//	vector<LPGAMEOBJECT>::iterator it;
//	for (it = objects.begin(); it != objects.end(); it++)
//	{
//		delete (*it);
//	}
//	objects.clear();
//}
//
///*
//	Unload scene
//
//	TODO: Beside objects, we need to clean up sprites, animations and textures as well
//
//*/
//void CPlayScene::Unload()
//{
//	for (int i = 0; i < objects.size(); i++)
//		delete objects[i];
//
//	objects.clear();
//	player = NULL;
//
//	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
//}
//
//bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
//
//void CPlayScene::PurgeDeletedObjects()
//{
//	vector<LPGAMEOBJECT>::iterator it;
//	for (it = objects.begin(); it != objects.end(); it++)
//	{
//		LPGAMEOBJECT o = *it;
//		if (o->IsDeleted())
//		{
//			delete o;
//			*it = NULL;
//		}
//	}
//
//	// NOTE: remove_if will swap all deleted items to the end of the vector
//	// then simply trim the vector, this is much more efficient than deleting individual items
//	objects.erase(
//		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
//		objects.end());
//}
//
//void CPlayScene::AddObject(LPGAMEOBJECT object)
//{
//	AddObjectToQuadTree(object);
//	objects.insert(objects.begin() + 1, object);
//
//}

#include <iostream>
#include <fstream>

#include "PlayScene.h"
#include "Game.h"
//#include "Bullet.h"
#include "Utils.h"
#include "Sprites.h"
//#include "BillInputHandler.h"
#include "Soldier.h"
#include "Bill.h"
//#include "Grass.h"
//#include "GunRotation.h"
//#include "Sniper.h"
#include <unordered_set>
#include "Textures.cpp"
//#include "HiddenSniper.h"
//#include "BlockObject.h"

using namespace std;

#define OBJECT_TYPE_BILL 1

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	//key_handler = new CBillInputHandler();
	QuadTree = NULL;
	/*this->camB = 0;
	this->camL = 0;
	this->camR = 0;
	this->camT = 0;*/
}

#define FULL_WEIGHT_1_1 2816
#define ADJUST_CAMERA_X	264
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_TILEMAP_DATA	3
#define SCENE_SECTION_TILEMAP_HIDDEN 4
#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ADJUST_CAM_MIN_Y 224
#define ADJUST_CAM_MAX_Y 256

#define MAX_SCENE_LINE 1024

void CPlayScene::AddObject(LPGAMEOBJECT object)
{
	AddObjectToQuadTree(object);
	objects.insert(objects.begin() + 1, object);
}
void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		//DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}
void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_TILEMAP_DATA(string line)
{
	int ID, rowMap, columnMap, columnTile, rowTile, totalTiles, startX, startY;
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f;

	f.open(path);
	f >> ID >> rowMap >> columnMap >> rowTile >> columnTile >> totalTiles >> startX >> startY;
	//Init Map Matrix

	int** TileMapData = new int* [rowMap];
	for (int i = 0; i < rowMap; i++)
	{
		TileMapData[i] = new int[columnMap];
		for (int j = 0; j < columnMap; j++)
		{
			f >> TileMapData[i][j];
		}

	}
	f.close();

	//current_map = new CMap(ID, rowMap, columnMap, rowTile, columnTile, totalTiles, startX, startY);
	//current_map->ExtractTileFromTileSet();
	//current_map->SetTileMapData(TileMapData);
}


void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (unsigned int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BILL:
		if (player != NULL)
		{
			//debugout(l"[error] mario object was created before!\n");
			return;
		}
		obj = new CBill(x, y);
		player = (CBill*)obj;

		//debugout(l"[info] player object has been created!\n");
		break;
	//case ID_SOLDIER: obj = new CSoldier(x, y); break;
	//case ID_BLOCK_OBJECT: obj = new CBlockObject(x, y, atoi(tokens[3].c_str())); break;
	//case ID_SNIPER: obj = new CSniper(x, y); break;
		/*case ID_GUNROTATION: obj = new CGunRotation(x, y); break;
		case ID_SNIPER_HIDDEN: obj = new CHiddenSniper(x, y); break;*/

	default:
		//debugout(l"[error] invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	if (!dynamic_cast<CBill*>(obj))
		QuadTree->AddObject(obj);
	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	//DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	//DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{

	//DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; QuadTree = new TreeNode(0, 0, 40, 40); continue; };
		if (line == "[TILEMAP]") { section = SCENE_SECTION_TILEMAP_DATA; continue; }
		if (line == "[HIDDENMAP]") { section = SCENE_SECTION_TILEMAP_HIDDEN; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP_DATA: _ParseSection_TILEMAP_DATA(line); break;
		}
	}
	f.close();
	ammo = new vector<CBullet*>();
	//DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	QuadTree->Split();
	//QuadTree->Split();
}

void CPlayScene::Update(DWORD dt)
{
	unordered_set<LPGAMEOBJECT> coObjects;
	vector<LPTREENODE>* treeNodeList = QuadTree->NodeInCam();
	for (int i = 0; i < treeNodeList->size(); i++)
	{
		vector<LPGAMEOBJECT>* gameObjectsList = treeNodeList->at(i)->GetObject();
		if (gameObjectsList != NULL)
		{
			for (int i = 0; i < gameObjectsList->size(); i++)
				coObjects.insert(gameObjectsList->at(i));
		}
	}
	vector<LPGAMEOBJECT> object;
	object.insert(object.end(), coObjects.begin(), coObjects.end());
	for (size_t i = 0; i < object.size(); i++)
	{
		object.at(i)->Update(dt, &object);
		QuadTree->Update(object.at(i));
	}
	player->Update(dt, &object);
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow marioD
	float cx, cy;
	player->GetPosition(cx, cy);
	//for (int i = 0; i < ammo->size(); i++)
	//	ammo->at(i)->Update(dt, &object);
	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy = 0;
	if (cx < 0) cx = 0;
	if (cx > FULL_WEIGHT_1_1 - ADJUST_CAMERA_X) cx = FULL_WEIGHT_1_1 - ADJUST_CAMERA_X;


	if (cy > ADJUST_CAM_MAX_Y) cy = ADJUST_CAM_MAX_Y;
	else if ((ADJUST_CAM_MIN_Y < cy) && (cy < ADJUST_CAM_MAX_Y)) cy = ADJUST_CAM_MAX_Y;
	else  cy = ADJUST_CAM_MAX_Y + cy - ADJUST_CAM_MIN_Y;
	//else if (cy < ADJUST_CAM_MAX_Y) cy =  cy+ ADJUST_CAM_MAX_Y ;
	if (cy < 0) cy = 0;

	CGame::GetInstance()->SetCamPos(cx, cy);


	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	CGame* game = CGame::GetInstance();

	//current_map->Render();

	unordered_set<LPGAMEOBJECT> coObjects;
	vector<LPTREENODE>* treeNodeList = QuadTree->NodeInCam();
	for (int i = 0; i < treeNodeList->size(); i++)
	{
		vector<LPGAMEOBJECT>* gameObjectsList = treeNodeList->at(i)->GetObject();
		if (gameObjectsList != NULL)
		{
			for (int i = 0; i < gameObjectsList->size(); i++)
				coObjects.insert(gameObjectsList->at(i));
		}
	}
	for (auto i = coObjects.begin(); i != coObjects.end(); ++i)
		(*i)->Render();
	//for (auto i = ammo->begin(); i != ammo->end(); ++i)
	//	(*i)->Render();
	player->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene
	TODO: Beside objects, we need to clean up sprites, animations and textures as well
*/
void CPlayScene::Unload()
{

	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	//delete current_map;
	//delete hidden_map;
	//current_map = nullptr;
	player = NULL;

	//DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& obj) { return obj == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}