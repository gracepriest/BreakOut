#pragma once
#include "CommonHeaders.h"
#include "Graphics.h"
using namespace std;

//typedef Texture2D paddle;
extern vector<Texture2D> Paddles;
static Image quad;
static Texture2D quadtTexture;

void static InitPaddleQuad()
{
	float x =0, y = 64;
	Rectangle rec{ x,y,32,16 };
	Image mainImage = LoadImageFromTexture(MAIN);

	for (int i = 0; i < 4; i++)
	{
		rec = { x,y ,32 , 16 };
		quad = ImageFromImage(mainImage, rec);
		quadtTexture = LoadTextureFromImage(quad);
		Paddles.push_back(quadtTexture);

		rec = { x+32,y ,64 , 16 };
		quad = ImageFromImage(mainImage, rec);
		quadtTexture = LoadTextureFromImage(quad);
		Paddles.push_back(quadtTexture);

		rec = { x+96,y ,96 , 16 };
		quad = ImageFromImage(mainImage, rec);
		quadtTexture = LoadTextureFromImage(quad);
		Paddles.push_back(quadtTexture);

		rec = { x,y+16,128 , 16 };
		quad = ImageFromImage(mainImage, rec);
		quadtTexture = LoadTextureFromImage(quad);
		Paddles.push_back(quadtTexture);

		x = 0;
		y = y + 32;

	}
	
	

}


class Paddle
{
public:
	float x;
	float y;
	float dx;
	float width;
	float height;
	float skin;
	int health;
	//size of paddle
	float size;
	const float PADDLE_SPEED = 350;
	vector<Texture2D> paddleImage;
	Paddle();
	void Update(float dt);
	
	void Render();
	void Reset();
	
	~Paddle() {};
};

