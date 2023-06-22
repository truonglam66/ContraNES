#pragma once
#include "Font.h"
#include "GameObject.h"

class CText : public CGameObject
{
protected:
	string text;
public:
	CText(float x, float y, string text) :CGameObject(x, y) {
		this->text = text;
	}
	void Render()
	{
		CFont::GetInstance()->DrawString(text, x, y);
	}
};