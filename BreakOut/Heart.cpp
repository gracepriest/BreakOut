#include "Heart.h"


Heart::Heart()
{
	y = 0;
	x = 700;
	width = 8;
	height = 8;
	inPlay = true;
	scale = 2;

}

void Heart::Render()
{
	if (inPlay)
	{

		//DrawTexture(Paddles[size + 4 * (skin -1)], x, y, WHITE);
		DrawTextureEx(heartImage, Vector2{ x,y }, 0, scale, WHITE);
		//testing
		//DrawRectangleRec(recMask, Color{ 255,255, 255, 128 });
	}
	else
	{
		
		DrawTextureEx(Hearts[1], Vector2{ x,y }, 0, scale, WHITE);
	}
}