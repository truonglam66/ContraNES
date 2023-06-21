#include "Sprite.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth();
	sprite.TexCoord.y = this->top / (float)tex->getHeight();

	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);
}

void CSprite::Draw(float x, float y)
{
	//cam
	CGame* g = CGame::GetInstance();
	D3DXVECTOR2 camPos;
	g->GetCamPos(camPos.x, camPos.y);
	camPos.x = (FLOAT)floor(camPos.x);
	camPos.y = (FLOAT)floor(camPos.y);
	int cam_h = g->GetBackBufferHeight();

	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, x - camPos.x, -g->GetBackBufferHeight() + camPos.y + y, 0.1f);
	this->sprite.matWorld = (this->matScaling * matTranslation);

	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}