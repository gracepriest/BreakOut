#include "Paddle.h"

vector<Texture2D> Paddles;

Paddle::Paddle()
{
	size = 2;
	x = 550;
	y = 650;
	dx = 0;
	skin = 1;
	width = 192;
	height = 16;
	health = 3;
}

void Paddle::Update(float dt)
{
	float zero = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		dx = -PADDLE_SPEED;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		dx = PADDLE_SPEED;
	}
	else
	{
		dx = 0;
	}

	if (dx < 0)
	{
		x = max(zero, x + dx * dt);
	}
	else
	{
		x = min((float)WINDOW_WIDTH-width, x + dx * dt);
	}
}

void Paddle::Render()
{
	//DrawTexture(Paddles[size + 4 * (skin -1)], x, y, WHITE);
	DrawTextureEx(Paddles[size + 4 * (skin - 1)], Vector2{ x,y }, 0, 2, WHITE);
}

void Paddle::Reset()
{
	x = 550;
	y = 650;
}