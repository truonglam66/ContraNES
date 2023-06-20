#pragma once
#include "GameObject.h"
#include "Bullet.h"

#define BILL_BULLET_WIDTH 4
#define BILL_BULLET_HEIGHT 4
class CBillBullet : public CBullet
{
public:
	CBillBullet(float x, float y, float vx, float vy);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};