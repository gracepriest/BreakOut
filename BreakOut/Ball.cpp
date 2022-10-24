#include "Ball.h"


using namespace std;
class Paddle;

//Sound HIT_PADDLE;

Ball::Ball()
{
	size = 1;
	x = 645;
	y = 600;
	dx = 0;
	dy = 0;
	skin = 0;
	width = 8;
	height = 8;
	scale = 2;
	recMask.height = height * scale;
	recMask.width = width * scale;
	recMask.x = x;
	recMask.y = y;
	
}



void Ball::Update(float dt)
{
	
	x += dx * dt;
	y += dy * dt;

	if (x < 0)
	{
		x = 0;
		dx = -dx;
		//sound
		PlaySound(HIT_WALL);
	}
	else if(x > WINDOW_WIDTH - 8)
	{
		x = WINDOW_WIDTH - 8;
		dx = -dx;
		//sound
		PlaySound(HIT_WALL);
	}
	if (y < 0)
	{
		y = 0;
		dy = -dy;
		//sound
		PlaySound(HIT_WALL);
	}
	recMask.x = x;
	recMask.y = y;
}
void Ball::Render()
{
	string strDx = to_string(dy);
	//DrawTexture(Balls[size + 4 * (skin -1)], x, y, WHITE);
	DrawTextureEx(Balls[size], Vector2{ x,y }, 0, scale, WHITE);
	//testing
	//DrawText(strDx.c_str(), 0, 150,LARGE,BLACK);
	//DrawRectangleRec(recMask, Color{ 255,255, 255, 128 });
	
}

bool Ball::Collide(Brick target)
{
	return CheckCollisionRecs(recMask, target.recMask);
}

void Ball::Reset()
{
	x = 645;
	y = 600;
}
