#include "Soldier2.h"

CSoldier2::CSoldier2(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	die_start = -1;
	SetState(SOLDIER_STATE_RUNNING_LEFT);
}

void CSoldier2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*if (state == SOLDIER_STATE_DIE)
	{
		left = x - SOLDIER_BBOX_WIDTH / 2;
		top = y - SOLDIER_BBOX_HEIGHT_DIE / 2;
		right = left + SOLDIER_BBOX_WIDTH;
		bottom = top + SOLDIER_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - SOLDIER_BBOX_WIDTH / 2;
		top = y - SOLDIER_BBOX_HEIGHT / 2;
		right = left + SOLDIER_BBOX_WIDTH;
		bottom = top + SOLDIER_BBOX_HEIGHT;
	}*/
}

void CSoldier2::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSoldier2::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSoldier2*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CSoldier2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (x < 0) {
		vx = -vx;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CSoldier2::Render()
{
	CAnimations::GetInstance()->Get(1200)->Render(x, y);
	RenderBoundingBox();
}

void CSoldier2::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case SOLDIER_STATE_RUNNING_RIGHT:
	//	vx = SOLDIER_RUNNING_SPEED;
	//	vy = 0;
	//	break;
	//}
	vx = 0;
	vy = 0;
}
