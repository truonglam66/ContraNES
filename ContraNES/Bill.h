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

#define BILL_GRAVITY			-0.002f

#define BILL_STATE_IDLE				1
#define BILL_STATE_WALKING_RIGHT	2
#define BILL_STATE_WALKING_LEFT		3

#define BILL_STATE_JUMP				4

#define BILL_STATE_RUNNING_RIGHT	5
#define BILL_STATE_RUNNING_LEFT		6

#define BILL_STATE_SIT				7
#define BILL_STATE_SIT_RELEASE		8
#define BILL_STATE_DIE				9

#define BILL_STATE_RELEASE_JUMP		10


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

#define ID_ANI_BILL_DIE	1002
#pragma endregion
#define BILL_WIDTH 14

class CBill : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;
	void OnCollisionWithGround(LPCOLLISIONEVENT e);
	void OnCollisionWithSoldier(LPCOLLISIONEVENT e);
	//void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	//void OnCollisionWithPortal(LPCOLLISIONEVENT e);

public:
	CBill(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != BILL_STATE_DIE);
	}

	int IsBlocking() { return (state != BILL_STATE_DIE); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};