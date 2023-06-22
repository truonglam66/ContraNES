#pragma once
#include "Animations.h"
#include "Textures.h"
#include <string>
#include <string.h>
#include <unordered_map>

using namespace std;
#define CHAR_W	6
#define CHAR_H	6
#define FONT_TEXTURE_ID 9999
#define FONT_TEXTURE_WIDTH 48
#define FONT_TEXTURE_HEIGHT 72
#define NUM_COLUMN 6
#define SPACE 2 //khoang cach giua 2 ki tu

class CFont
{
	static CFont* __instance;
	unordered_map<char, LPSPRITE> charSet;
public:
	CFont();
	~CFont();
	void AddFontSprite();
	void DrawString(string string, float x, float y);
	static CFont* GetInstance();
};