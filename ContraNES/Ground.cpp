#include "Ground.h"

CGround::CGround(float x, float y, int width, int height) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void CGround::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	right = x + width / 2;
	top = y + height / 2;
	bottom = y - height / 2;
}

void CGround::OnNoCollision(DWORD dt)
{
};

void CGround::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGround::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	//int aniId = 88888;
	//animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGround::SetState(int state)
{
	CGameObject::SetState(state);
}