#pragma once
#include "CommonHeaders.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Brick.h"



extern std::vector<Texture2D> Balls;
static Image ballQuad;
static Texture2D ballQuadtTexture;


static void InitBall()
{
	float x = 96, y = 48;
	Rectangle rec{ x,y,8,8 };
	Image mainImage = LoadImageFromTexture(MAIN);

	for (int i = 0; i < 4; i++)
	{
		rec = { x,y ,8 , 8 };
		ballQuad = ImageFromImage(mainImage, rec);
		ballQuadtTexture = LoadTextureFromImage(ballQuad);
		Balls.push_back(ballQuadtTexture);
		x += 8;
	}

	x = 96;
	y = 56;

	for (int i = 0; i < 3; i++)
	{
		rec = { x,y ,8 , 8 };
		ballQuad = ImageFromImage(mainImage, rec);
		ballQuadtTexture = LoadTextureFromImage(ballQuad);
		Balls.push_back(ballQuadtTexture);
		x += 8;
	}
}

class Ball
{
public:

	float x;
	float y;
	float dx;
	float dy;
	float width;
	float height;
	float skin;
	//size of ball
	float size;
	float BALL_SPEED = 1;
	Rectangle recMask;
	float scale;


	Ball();
	void Update(float dt);

	
	template <typename T>
	bool Collides(T target)
	{ 
	  //aabb collision detection
	  //return false if no collision return true if collision
		
	
		if (x + width > target.x && x < target.x + target.width && y + height > target.y && y < target.y + target.height)
		{
			return true;
		}
		return false;
	}
	
	bool Collide(Brick target);
	
	
	void Render();
	void Reset();

	~Ball() {};
};