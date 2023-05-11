#include "Soldier.h"

CSoldier::CSoldier(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SOLDIER_GRAVITY;
	die_start = -1;
	SetState(SOLDIER_STATE_RUNNING_LEFT);
}

void CSoldier::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 22 / 2;
	top = y - 28 / 2;
	right = left + 22;
	bottom = top + 28;
}

void CSoldier::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSoldier::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSoldier*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		//vx = 0;
		SetState(SOLDIER_STATE_DIE);
	}
}

void CSoldier::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (x < 0) {
		vx = -vx;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSoldier::Render()
{
	int aniId;
	switch (state)
	{
	case SOLDIER_STATE_RUNNING_RIGHT:
		aniId = ID_ANI_SOLDIER_RUNNING_RIGHT;
		break;
	case SOLDIER_STATE_SHOOT_RIGHT:
		aniId = ID_ANI_SOLDIER_SHOOTING_RIGHT;
		break;
	case SOLDIER_STATE_LAY:
		aniId = ID_ANI_SOLDIER_LAY;
		break;
	case SOLDIER_STATE_JUMP:
		aniId = ID_ANI_SOLDIER_JUMP;
		break;
	case SOLDIER_STATE_RUNNING_LEFT:
		aniId = ID_ANI_SOLDIER_RUNNING_LEFT;
		break;
	case SOLDIER_STATE_IDLE:
		aniId = ID_ANI_SOLDIER_IDLE;
		break;
	case SOLDIER_STATE_DIE:
		aniId = ID_ANI_SOLDIER_DIE;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CSoldier::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOLDIER_STATE_RUNNING_RIGHT:
		vx = SOLDIER_RUNNING_SPEED;
		vy = 0;
		break;
	case SOLDIER_STATE_SHOOT_RIGHT:
		vx = 0;
		vy = 0;
		break;
	case SOLDIER_STATE_LAY:
		vx = 0;
		vy = 0;
		break;
	case SOLDIER_STATE_JUMP:
		vx = 0;
		vy = 0;
		break;
	case SOLDIER_STATE_RUNNING_LEFT:
		vx = 0;// -SOLDIER_RUNNING_SPEED;
		vy = 0;
		break;
	case SOLDIER_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SOLDIER_STATE_DIE:
		vx = 0;
		vy = 0;
		y = y - 50;
		break;
	}
}