#include "Brick.h"
using namespace std;


Brick::Brick()
{
	x = 150;
	y = 100;
	width = 32;
	height = 16;
	color = 1;
	inPlay = true;
	tier = 0;
	scale = 3;
	recMask.height = height * scale;
	recMask.width = width * scale;
	recMask.x = x;
	recMask.y = y;
}

void Brick::Hit()
{
	if (tier > 0)
	{
		if (color == 1)
		{

			tier -= 2;
			if (tier < 0)
			{
				tier = 0;
			}
			color = 1;

		}
		else
		{
			color -= 1;
		}
	}
	else
		//if were in the first tier and the base color, remove brick from play
	{
		if (color == 1)
		{
			inPlay = false;
		}
		else
		{
			color -= 1;
		}
	}
	
}

void Brick::Render()
{
	if (inPlay)
	{

	//DrawTexture(Paddles[size + 4 * (skin -1)], x, y, WHITE);
	DrawTextureEx(Bricks[((color-1) *4) + tier], Vector2{ x,y }, 0, scale, WHITE);
	//testing
	//DrawRectangleRec(recMask, Color{ 255,255, 255, 128 });
	
	}
}


