#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Bill.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CBill* bill = (CBill*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		bill->SetState(BILL_STATE_SIT);
		break;
	case DIK_S:
		bill->SetState(BILL_STATE_JUMP);
		break;
	case DIK_0:
		bill->SetState(BILL_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CBill* bill = (CBill*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		bill->SetState(BILL_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		bill->SetState(BILL_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CBill* bill = (CBill*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			bill->SetState(BILL_STATE_RUNNING_RIGHT);
		else
			bill->SetState(BILL_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			bill->SetState(BILL_STATE_RUNNING_LEFT);
		else
			bill->SetState(BILL_STATE_WALKING_LEFT);
	}
	else
		bill->SetState(BILL_STATE_IDLE);
}