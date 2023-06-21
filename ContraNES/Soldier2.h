#pragma once
#include "GameObject.h"

#define SOLDIER_GRAVITY 0 //0.002f
#define SOLDIER_RUNNING_SPEED 0.05f

#define SOLDIER_STATE_RUNNING_RIGHT	0
#define SOLDIER_STATE_SHOOT_RIGHT	1
#define SOLDIER_STATE_LAY	2
#define SOLDIER_STATE_JUMP	3
#define SOLDIER_STATE_RUNNING_LEFT	4

#define ID_ANI_SOLDIER_RUNNING_RIGHT 1100
#define ID_ANI_SOLDIER_SHOOTING_RIGHT 1101
#define ID_ANI_SOLDIER_LAY 1102
#define ID_ANI_SOLDIER_JUMP 1103
#define ID_ANI_SOLDIER_RUNNING_LEFT 1104

class CSoldier2 : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CSoldier2(float x, float y);
	virtual void SetState(int state);
};