#include "Game.h"
#include "Bill.h"

CBill::CBill(float x, float y):CGameObject(x, y)
{
	SetState(BILL_STATE_RUNNING_RIGHT);
};

void CBill::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//Get bbox
}

void CBill::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx*dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - BILL_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - BILL_WIDTH)
		{
			x = (float)(BackBufferWidth - BILL_WIDTH);
		}
	}
}

void CBill::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx>0) ani = CAnimations::GetInstance()->Get(101);
	else ani = CAnimations::GetInstance()->Get(102);

	ani->Render(x, y);
}

void CBill::SetState(int state)
{
	
}