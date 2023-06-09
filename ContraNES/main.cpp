/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"
#include "Bill.h"
#include"Background.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Bill - Run Shoot Jump Swim"
#define WINDOW_ICON_PATH L"contra.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_BILL 30
#define ID_TEX_FLIPBILL 1
#define ID_TEX_BACKGROUND 2


#define TEXTURES_DIR L"textures"
#define TEXTURES_DIR_1 L"resources"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_BILL TEXTURES_DIR_1 "\\Bill.png"
#define TEXTURE_PATH_FLIPBILL TEXTURES_DIR_1 "\\flipbill.png"
#define TEXTURE_PATH_BACKGROUND TEXTURES_DIR_1 "\\background.png"



CBill *bill;
#define BILL_START_X 10.0f
#define BILL_START_Y 130.0f
#define BILL_START_VX 0.1f

CBackground *background;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BILL, TEXTURE_PATH_BILL);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_FLIPBILL, TEXTURE_PATH_FLIPBILL);
	textures->Add(ID_TEX_BACKGROUND, TEXTURE_PATH_BACKGROUND);

	CSprites * sprites = CSprites::GetInstance();
	
	LPTEXTURE texBill = textures->Get(ID_TEX_BILL);
	LPTEXTURE texFlipBill = textures->Get(ID_TEX_FLIPBILL);
	LPTEXTURE texBackground = textures->Get(ID_TEX_BACKGROUND);




	// readline => id, left, top, right , bottom

	sprites->Add(99999, 0, 0, 3456, 245, texBackground);
	
	//Bill-Run - Shoot - Jump
	sprites->Add(10001, 25, 24, 44, 59, texBill);
	sprites->Add(10002, 90, 27, 110, 58, texBill);
	sprites->Add(10003, 157, 25, 173, 59, texBill);
	sprites->Add(10004, 220, 25, 238, 59, texBill);
	sprites->Add(10005, 285, 27, 305, 58, texBill);
	sprites->Add(10006, 353, 24, 369, 59, texBill);

	sprites->Add(10007, 415, 25, 440, 59, texBill);
	sprites->Add(10008, 480, 26, 505, 58, texBill);
	sprites->Add(10009, 547, 25, 570, 59, texBill);
	sprites->Add(10010, 610, 26, 635, 59, texBill);
	sprites->Add(10011, 675, 27, 700, 58, texBill);
	sprites->Add(10012, 742, 26, 765, 59, texBill);

	sprites->Add(10013, 805, 98, 821, 118, texBill);
	sprites->Add(10014, 868, 99, 887, 115, texBill);
	sprites->Add(10015, 935, 96, 951, 116, texBill);
	sprites->Add(10016, 999, 99, 1018, 115, texBill);
	

	//Bill-Swim
	sprites->Add(10200, 25, 167, 41, 180, texBill);
	sprites->Add(10201, 90, 160, 106, 175, texBill);
	sprites->Add(10202, 155, 159, 171, 174, texBill);
	sprites->Add(10203, 220, 157, 245, 173, texBill);
	sprites->Add(10204, 285, 156, 310, 173, texBill);
	sprites->Add(10205, 350, 156, 369, 173, texBill);
	sprites->Add(10206, 415, 155, 434, 173, texBill);
	sprites->Add(10207, 480, 146, 497, 173, texBill);
	sprites->Add(10208, 545, 145, 562, 173, texBill);
	sprites->Add(10209, 610, 167, 626, 174, texBill);
	sprites->Add(10210, 675, 166, 691, 173, texBill);

	//Bill-Flip Swim
	sprites->Add(10300, 2040, 167, 2056, 180, texFlipBill);
	sprites->Add(10301, 1975, 160, 1991, 175, texFlipBill);
	sprites->Add(10302, 1910, 159, 1926, 174, texFlipBill);
	sprites->Add(10303, 1836, 157, 1861, 173, texFlipBill);
	sprites->Add(10304, 1771, 156, 1796, 173, texFlipBill);
	sprites->Add(10305, 1712, 156, 1731, 173, texFlipBill);
	sprites->Add(10306, 1647, 155, 1666, 173, texFlipBill);
	sprites->Add(10307, 1584, 146, 1601, 173, texFlipBill);
	sprites->Add(10308, 1519, 145, 1536, 173, texFlipBill);
	sprites->Add(10309, 1455, 167, 1471, 174, texFlipBill);
	sprites->Add(10310, 1390, 166, 1406, 173, texFlipBill);
	sprites->Add(10311, 1325, 167, 1341, 183, texFlipBill);

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;
	
	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	ani->Add(10009);
	ani->Add(10010);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	ani->Add(10200);
	ani->Add(10201);
	ani->Add(10202);
	ani->Add(10203);
	ani->Add(10204);
	ani->Add(10205);
	ani->Add(10206);
	ani->Add(10207);
	ani->Add(10208);
	ani->Add(10209);
	ani->Add(10210);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10300);
	ani->Add(10301);
	ani->Add(10302);
	ani->Add(10303);
	ani->Add(10304);
	ani->Add(10305);
	ani->Add(10306);
	ani->Add(10307);
	ani->Add(10308);
	ani->Add(10309);
	ani->Add(10310);
	ani->Add(10311);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(99999);
	animations->Add(502, ani);
	/*ani = new CAnimation(100);
	ani->Add(10300);
	ani->Add(10301);
	ani->Add(10302);
	ani->Add(10303);
	ani->Add(10304);
	ani->Add(10305);
	ani->Add(10306);
	ani->Add(10307);
	ani->Add(10308);
	ani->Add(10309);
	ani->Add(10310);
	ani->Add(10311);
	animations->Add(501, ani);*/


	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 300, 117, 317, 133, texMisc);
	sprites->Add(20002, 318, 117, 335, 133, texMisc);
	sprites->Add(20003, 336, 117, 353, 133, texMisc);
	sprites->Add(20004, 354, 117, 371, 133, texMisc);

	ani = new CAnimation(100);
	ani->Add(20001, 1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);
	
	bill = new CBill(BILL_START_X, BILL_START_Y, BILL_START_VX);
	//background = new CBackground(0, 120);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	bill->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		//background->Render();
		bill->Render();
		

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0,0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		//DebugOut((wchar_t*)L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}