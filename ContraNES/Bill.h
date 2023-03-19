#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define BILL_WIDTH 14

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CBill : public CGameObject
{
protected:
	float vx;
public:
	CBill(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};


