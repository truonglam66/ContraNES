#pragma once
#include "Font.h"
#include "GameObject.h"

class CText : CGameObject
{
protected:
	string text;
public:
	CText(float x, float y, string text);
	void Render();
};