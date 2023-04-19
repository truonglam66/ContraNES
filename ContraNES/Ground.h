#pragma once
#include "GameObject.h"

class CGround : public CGameObject
{
protected:
	int width;
	int height;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGround(float x, float y, int width, int height);
	virtual void SetState(int state);
	void RenderBoundingBox() {};
};