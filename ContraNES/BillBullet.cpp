#include "Game.h"
#include "BillBullet.h"
#include "Soldier.h"
#include "Utils.h"
#include "debug.h"

void CBillBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CBillBullet::Render()
{
}

void CBillBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	CGame* game = CGame::GetInstance();
	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	float camW, camH;
	camW = CGame::GetInstance()->GetScreenWidth();
	camH = CGame::GetInstance()->GetScreenHeight();
	float boundaryL = camX - BILL_BULLET_WIDTH / 2; //vien dan ra khoi man hinh
	float boundaryT = camY + BILL_BULLET_HEIGHT / 2;
	float boundaryR = camX + camW + BILL_BULLET_WIDTH/2; //vien dan ra khoi man hinh
	float boundaryB = camY - camH - BILL_BULLET_HEIGHT / 2;
	if (x < boundaryL || x > boundaryR || y < boundaryB || y > boundaryT) {
		isDeleted = true;
	}
}

void CBillBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
}

void CBillBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*
	left = x - BILL_BULLET_WIDTH/2;
	top = y + BILL_BULLET_HEIGHT/2;
	right = x + BILL_BULLET_WIDTH/2;
	bottom = y - BILL_BULLET_HEIGHT/2;
	*/
}