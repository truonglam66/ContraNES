#pragma once
#include "GameObject.h"
class CBullet : public CGameObject
{
public:
	CBullet(float x, float y, float vx = 0.5f, float vy = 0.0f) {
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void DeleteBullet() {
		//deleted = 1???
	}
}