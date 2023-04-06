#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define BILL_WALKING_SPEED		0.1f
#define BILL_RUNNING_SPEED		0.2f

#define BILL_ACCEL_WALK_X	0.0005f
#define BILL_ACCEL_RUN_X	0.0007f

#define BILL_JUMP_SPEED_Y		0.5f
#define BILL_JUMP_RUN_SPEED_Y	0.6f

#define BILL_GRAVITY			0.002f

#define BILL_STATE_IDLE				1
#define BILL_STATE_WALKING_RIGHT	2
#define BILL_STATE_WALKING_LEFT		3

#define BILL_STATE_JUMP				4

#define BILL_STATE_RUNNING_RIGHT	5
#define BILL_STATE_RUNNING_LEFT		6

#define BILL_STATE_SIT				7
#define BILL_STATE_SIT_RELEASE		8

#pragma region ANIMATION_ID

#define ID_ANI_BILL_IDLE_RIGHT 400
#define ID_ANI_BILL_IDLE_LEFT 401

#define ID_ANI_BILL_WALKING_RIGHT 500
#define ID_ANI_BILL_WALKING_LEFT 501

#define ID_ANI_BILL_RUNNING_RIGHT 600
#define ID_ANI_BILL_RUNNING_LEFT 601

#define ID_ANI_BILL_JUMP_WALK_RIGHT 700
#define ID_ANI_BILL_JUMP_WALK_LEFT 701

#define ID_ANI_BILL_JUMP_RUN_RIGHT 800
#define ID_ANI_BILL_JUMP_RUN_LEFT 801

#define ID_ANI_BILL_SIT_RIGHT 900
#define ID_ANI_BILL_SIT_LEFT 901

#define ID_ANI_BILL_BRACE_RIGHT 1000
#define ID_ANI_BILL_BRACE_LEFT 1001

#pragma endregion
#define BILL_WIDTH 14

class CBill : public CGameObject
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
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBill(float x, float y);
	virtual void SetState(int state);
};


