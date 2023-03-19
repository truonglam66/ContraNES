#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 99999
#define BRICK_WIDTH 16

class CBackground : public CGameObject {
public:
	CBackground(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};