#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BACKGROUND 9999

class CBackground : public CGameObject {
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
public:
	CBackground(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};