#include "Game.h"
#include "Bill.h"

CBill::CBill(float x, float y):CGameObject(x, y)
{
	isSitting = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = BILL_GRAVITY;

	isOnPlatform = false;
	SetState(BILL_STATE_IDLE);
};

void CBill::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBill::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CBill::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	/*if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);*/
}

//void CBill::OnCollisionWithSoldier(LPCOLLISIONEVENT e)
//{
//	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
//
//	// jump on top >> kill Goomba and deflect a bit 
//	if (e->ny < 0)
//	{
//		if (goomba->GetState() != GOOMBA_STATE_DIE)
//		{
//			goomba->SetState(GOOMBA_STATE_DIE);
//			vy = -BILL_JUMP_DEFLECT_SPEED;
//		}
//	}
//	else // hit by Goomba
//	{
//		if (untouchable == 0)
//		{
//			if (goomba->GetState() != GOOMBA_STATE_DIE)
//			{
//				if (level > BILL_LEVEL_SMALL)
//				{
//					level = BILL_LEVEL_SMALL;
//					StartUntouchable();
//				}
//				else
//				{
//					DebugOut(L">>> Mario DIE >>> \n");
//					SetState(BILL_STATE_DIE);
//				}
//			}
//		}
//	}
//}

//void CBill::OnCollisionWithCoin(LPCOLLISIONEVENT e)
//{
//	e->obj->Delete();
//	coin++;
//}

//void CBill::OnCollisionWithPortal(LPCOLLISIONEVENT e)
//{
//	CPortal* p = (CPortal*)e->obj;
//	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
//}

//
// Get animation ID for small Mario
//

void CBill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId;
	switch (state)
	{
	case BILL_STATE_RUNNING_LEFT:
		aniId = 103;
		break;
	case BILL_STATE_RUNNING_RIGHT:
		aniId = 102;
		break;
	case BILL_STATE_IDLE:
		aniId = 101;
		break;
	case BILL_STATE_WALKING_RIGHT:
		aniId = 102;
		break;
	case BILL_STATE_WALKING_LEFT:
		aniId = 103;
		break;
	}
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CBill::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == BILL_STATE_DIE) return;

	switch (state)
	{
	case BILL_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = BILL_RUNNING_SPEED;
		ax = BILL_ACCEL_RUN_X;
		nx = 1;
		break;
	case BILL_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -BILL_RUNNING_SPEED;
		ax = -BILL_ACCEL_RUN_X;
		nx = -1;
		break;
	case BILL_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = BILL_WALKING_SPEED;
		ax = BILL_ACCEL_WALK_X;
		nx = 1;
		break;
	case BILL_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -BILL_WALKING_SPEED;
		ax = -BILL_ACCEL_WALK_X;
		nx = -1;
		break;
	case BILL_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == BILL_RUNNING_SPEED)
				vy = -BILL_JUMP_RUN_SPEED_Y;
			else
				vy = -BILL_JUMP_SPEED_Y;
		}
		break;

	case BILL_STATE_RELEASE_JUMP:
		if (vy < 0) vy += BILL_JUMP_SPEED_Y / 2;
		break;

	case BILL_STATE_SIT:
		if (isOnPlatform)
		{
			state = BILL_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			//y += BILL_SIT_HEIGHT_ADJUST;
		}
		break;

	case BILL_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = BILL_STATE_IDLE;
			//y -= BILL_SIT_HEIGHT_ADJUST;
		}
		break;

	case BILL_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case BILL_STATE_DIE:
		//vy = -BILL_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CBill::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//if (level == BILL_LEVEL_BIG)
	//{
	//	if (isSitting)
	//	{
	//		left = x - BILL_BIG_SITTING_BBOX_WIDTH / 2;
	//		top = y - BILL_BIG_SITTING_BBOX_HEIGHT / 2;
	//		right = left + BILL_BIG_SITTING_BBOX_WIDTH;
	//		bottom = top + BILL_BIG_SITTING_BBOX_HEIGHT;
	//	}
	//	else
	//	{
	//		left = x - BILL_BIG_BBOX_WIDTH / 2;
	//		top = y - BILL_BIG_BBOX_HEIGHT / 2;
	//		right = left + BILL_BIG_BBOX_WIDTH;
	//		bottom = top + BILL_BIG_BBOX_HEIGHT;
	//	}
	//}
	//else
	//{
	//	left = x - BILL_SMALL_BBOX_WIDTH / 2;
	//	top = y - BILL_SMALL_BBOX_HEIGHT / 2;
	//	right = left + BILL_SMALL_BBOX_WIDTH;
	//	bottom = top + BILL_SMALL_BBOX_HEIGHT;
	//}
}
