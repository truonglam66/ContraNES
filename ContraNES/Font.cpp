#include "Font.h"
CFont::CFont()
{
}

CFont::~CFont()
{
}

void CFont::AddFontSprite()
{
#define CHAR_H	6
#define FONT_TEXTURE_ID 9999
#define FONT_TEXTURE_WIDTH 48
#define FONT_TEXTURE_HEIGHT 72
#define NUM_COLUMN 6
#define SPACE 2 //khoang cach giua 2 ki tu

	LPTEXTURE textures = CTextures::GetInstance()->Get(FONT_TEXTURE_ID);
	//ki tu abc
	int id, left, top, right, bottom;
	for (int i = 0; i < 26; i++)
	{
		id = 97 + i;
		left = (i * (CHAR_W + SPACE)) % FONT_TEXTURE_WIDTH;
		top = i / NUM_COLUMN * (CHAR_H + SPACE);
		right = (i * (CHAR_W + SPACE) + CHAR_W) % FONT_TEXTURE_WIDTH;
		bottom = i / NUM_COLUMN * (CHAR_H + SPACE) + CHAR_H + SPACE - 1;
		charSet[char(id)] = new CSprite(id, left, top, right, bottom, textures);
	}
	//ki tu dac biet
	for (int i = 0; i < 10; i++)
	{
		id = 48 + i;
		left = (i + 26) * (CHAR_W + SPACE);
		top = (i + 26) / NUM_COLUMN * (CHAR_H + SPACE);
		right = (i + 26) * (CHAR_W + SPACE) + CHAR_W;
		bottom = (i + 26) / NUM_COLUMN * (CHAR_H + SPACE) + CHAR_H;
		charSet[char(id)] = new CSprite(id, left, top, right, bottom, textures);
	}
	//khoang trang
	charSet[char(32)] = new CSprite(32, FONT_TEXTURE_WIDTH - CHAR_W, FONT_TEXTURE_HEIGHT - CHAR_H, FONT_TEXTURE_WIDTH, FONT_TEXTURE_HEIGHT, textures);
}

void CFont::DrawString(string string, float x, float y)
{
	int length = string.length();
	for (int i = 0; i < length; i++)
		charSet[string[i]]->Draw(x + i * (CHAR_W + SPACE), y);
}
