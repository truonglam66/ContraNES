#include "Text.h"
CText::CText(float x, float y, string text) : CGameObject(x, y)
{
	this->text = text;
}

void CText::Render()
{
	CFont::GetInstance()->DrawString(text, x, y);
}

void CText::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
