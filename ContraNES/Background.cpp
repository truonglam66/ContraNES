#include "Background.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(502)->Render(x, y);
}