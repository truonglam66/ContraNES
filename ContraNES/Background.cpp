#include "Background.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(9999)->Render(x, y);
}