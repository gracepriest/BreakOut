#pragma once

#include "CommonHeaders.h"
#include "Graphics.h"

extern std::vector<Texture2D> Hearts;
static Image heartQuad;
static Texture2D heartQuadtTexture;


static void InitHeart()
{
	float x = 0, y = 0;
	Rectangle rec{ x,y,10,10 };
	Image mainImage = LoadImageFromTexture(HEARTS);

	for (int i = 0; i < 3; i++)
	{
		rec = { x,y ,10 , 8 };
		heartQuad = ImageFromImage(mainImage, rec);
		heartQuadtTexture = LoadTextureFromImage(heartQuad);
		Hearts.push_back(heartQuadtTexture);
		x += 10;
	}
	

}

class Heart
{
public:

	float x;
	float y;
	float width;
	float height;
	Texture2D heartImage;
	bool inPlay ;
	Heart();
	//void Update(float dt) {}
	Rectangle recMask;
	float scale;
	void Render();

	~Heart() {};
};


std::vector<Heart> static createHeartMap()
{

	std::vector<Heart> heart;
	int counter = 0;
	int Hspace = 0;
	int Vspace = 0;

	for (const auto& item : Hearts)
	{
		heart.push_back(Heart());
		heart[counter].heartImage = Hearts[0];
		heart[counter].x += Hspace;
		heart[counter].y += Vspace;
		heart[counter].recMask.x = heart[counter].x;
		heart[counter].recMask.y = heart[counter].y;

		counter++;
		Hspace += 20;
		

	}
	return heart;
}
