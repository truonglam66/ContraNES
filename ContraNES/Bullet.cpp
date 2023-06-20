#include "Bullet.h"

CBullet::CBullet(float x, float y, float vx, float vy) : CGameObject(x, y)
{
	this->vx = vx;
	this->vy = vy;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render()
{
}

void CBullet::OnNoCollision(DWORD dt)
{
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
