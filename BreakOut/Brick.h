#pragma once
#include "CommonHeaders.h"
#include "Graphics.h"


extern std::vector<Texture2D> Bricks;
static Image brickQuad;
static Texture2D brickQuadtTexture;
static int LEVEL = 0;

//USED TO MAKE PATTERN A SHAPE
enum Shape {
	NONE = 1,
	SINGLE_PYRAMID = 2,
	MULTI_PYRAMID = 3
};

//PER-ROW PATTERNS
enum per_row{
	SOLID ,     //ALL COLOR THE SAME IN THIS ROW
	ALTERNATE , //ALTERNATE COLOR IN THIS ROW
	SKIP ,      //SKIP EVERY OTHER BLOCK
	//NONE = 4       //NO BLOCK THIS ROW
};


static void InitBrick()
{
	float x = 0, y = 0;
	Rectangle rec{ x,y,32,16 };
	Image mainImage = LoadImageFromTexture(MAIN);
	for (int j = 0; j < 4; j ++)
	{
		for (int i = 0; i < 6; i++)
		{
			//only need the first three from 3 row
			if (j == 3)
			{
				i += 1;
			}
			
			rec = { x,y ,32 , 16 };
			brickQuad = ImageFromImage(mainImage, rec);
			brickQuadtTexture = LoadTextureFromImage(brickQuad);
			Bricks.push_back(brickQuadtTexture);
			x += 32;
			
		}
		x = 0;
		y += 16;
	}
	/*for (int i = 0; i <19; i++)
	{
		
		Bricks.push_back(brickQuadtTexture);
		
	}*/
}



class Brick
{
public:

	float x;
	float y;
	//float dx;
	//float dy;
	float width;
	float height;
	float tier;
	int color;
	Texture2D brickImage;
	bool inPlay =true;
	Brick();
	void Update(float dt) {}
	void Hit();
	Rectangle recMask;
	float scale;
	void Render();

	~Brick() {};
};


std::vector<Brick> static createMap(int level)
{
	int counter = 0;
	int Hspace = 0;
	int Vspace = 0;
	int itemCounter = 0;
	bool hFlag = true;
	int numberOfRows = 0;
	int numberOfColumns = 0;
	int brickCount = 0;
	int brickPos = 0;
	int brickColor = 0;
	int brickTier = 0;
	std::vector<per_row> row;

	std::vector<Brick> brick;
	switch (level)
	{
	case 1:
		
		counter = 0;
		itemCounter = 0;
		Hspace = 0;
		Vspace = 0;

		for (int item =0; item < 40; item++)
		{
			brick.push_back(Brick());
			brick[counter].brickImage = Bricks[0];
			brick[counter].x += Hspace;
			brick[counter].y += Vspace;
			brick[counter].recMask.x = brick[counter].x;
			brick[counter].recMask.y = brick[counter].y;

			counter++;
			Hspace += 96;
			if (counter % 10 == 0)
			{
				Hspace = 0;
				Vspace += 48;
			}
		}
		
		break;
	case 2:
		 counter = 0;
		 itemCounter = 0;
		 Hspace = 0;
	     Vspace = 0;
		 brick.clear();


		for (int i = 0; i <20; i++)
		{
			brick.push_back(Brick());
		}

		for (auto& item : brick)
		{
			item.brickImage = Bricks[itemCounter * 4];
			item.color = itemCounter + 1;
			item.x += Hspace;
			item.y += Vspace;
			item.recMask.x = item.x;
			item.recMask.y = item.y;

			counter++;
			Hspace += 192;
			if (counter % 5 == 0)
			{
				if (hFlag == true)
				{
					Hspace = 96;
					Vspace += 48;
					itemCounter++;
					hFlag = false;
				}
				else
				{
					Hspace = 0;
					Vspace += 48;
					itemCounter++;
					hFlag = true;
				}

			}
		}
		
		break;
	case 3:
		counter = 0;
		Hspace = 0;
		Vspace = 0;
		brick.clear();
		brickPos = 0;
		brickCount = 0;
		brickColor = rand() % 4 + 1;

		//random numnber of rows
		numberOfRows = 4;
		//random numner of column odd
		//numberOfColumns = rand() % 10 + 6;


		for (int i = 0; i < numberOfRows; i++)
		{
			row.push_back(per_row());
			row[i] = (per_row)(rand() % 3);
			if (row[i] == SOLID)
			{
				brickCount += 10;
			}
			else if (row[i] == ALTERNATE)
			{
				brickCount += 10;
			}
			else if (row[i] == SKIP)
			{
				brickCount += 5;
			}

		}
		for (int i = 0; i < brickCount; i++)
		{
			brick.push_back(Brick());
		}
		for (int i = 0; i < numberOfRows; i++)
		{
			if (row[i] == SOLID)
			{
				for (int j = 0; j < 10; j++)
				{

					brick[brickPos + j].brickImage = Bricks[brickColor];
					brick[brickPos + j].color = brickColor;
					//brick[brickPos + j].tier = brickColor;
					brick[brickPos + j].x += Hspace;
					brick[brickPos + j].y += Vspace;
					brick[brickPos + j].recMask.x = brick[brickPos + j].x;
					brick[brickPos + j].recMask.y = brick[brickPos + j].y;


					Hspace += 96;

				}

				Hspace = 0;
				brickPos += 10;

			}
			else if (row[i] == SKIP)
			{
				for (int l = 0; l < 5; l++)
				{
					brick[brickPos + l].brickImage = Bricks[0];
					brick[brickPos + l].color = 1;
					//brick[brickPos + l].tier = 0;
					brick[brickPos + l].x += Hspace;
					brick[brickPos + l].y += Vspace;
					brick[brickPos + l].recMask.x = brick[brickPos + l].x;
					brick[brickPos + l].recMask.y = brick[brickPos + l].y;


					Hspace += 192;

				}

				Hspace = 0;
				brickPos += 5;
			}
			else if (row[i] == ALTERNATE) {

				for (int t = 0; t < 10; t++)

				{
					brick[brickPos + t].brickImage = Bricks[rand() % 4 * 4];
					brick[brickPos + t].color = rand() % 4 + 1;
					//brick[brickPos + t].tier = brick[brickPos +t].color;
					brick[brickPos + t].x += Hspace;
					brick[brickPos + t].y += Vspace;
					brick[brickPos + t].recMask.x = brick[brickPos + t].x;
					brick[brickPos + t].recMask.y = brick[brickPos + t].y;


					Hspace += 96;

				}
				Hspace = 0;
				brickPos += 10;


			}

			counter++;
			Hspace = 0;
			Vspace += 48;
		}

		break;
	default: //random layout
		counter = 0;
		Hspace = 0;
		Vspace = 0;
		brick.clear();
		brickPos = 0;
		brickCount = 0;
		brickColor = rand() % 4 +1;
		brickTier  = rand() % 3 + 1;

		//random numnber of rows
		numberOfRows =  4;
		//random numner of column odd
		//numberOfColumns = rand() % 10 + 6;

	
		for (int i = 0; i < numberOfRows; i++)
		{
			row.push_back(per_row());
			row[i] = (per_row)(rand() % 3);
			if (row[i] == SOLID)
			{
				brickCount += 10;
			}
			else if(row[i] == ALTERNATE)
			{
				brickCount += 10;
			}
			else if (row[i] == SKIP)
			{
				brickCount += 5;
			}

		}
		for (int i = 0; i < brickCount; i++)
		{
			brick.push_back(Brick());
		}
		for (int i =0; i < numberOfRows; i++)
		{
			if (row[i] == SOLID)
			{
				for (int j = 0; j < 10; j++)
				{
					
					brick[brickPos + j].brickImage = Bricks[brickColor];
					brick[brickPos + j].color = brickColor;
					brick[brickPos + j].tier = brickTier;
					brick[brickPos + j].x += Hspace;
					brick[brickPos + j].y += Vspace;
					brick[brickPos + j].recMask.x = brick[brickPos + j].x;
					brick[brickPos + j].recMask.y = brick[brickPos + j].y;

					
					Hspace += 96;
					
				}
				
				Hspace = 0;
				brickPos += 10;
				
			}
			else if (row[i] == SKIP)
			{
				for (int l = 0; l < 5; l++)
				{
					brick[brickPos +l].brickImage = Bricks[0];
					brick[brickPos + l].color = 1;
					brick[brickPos + l].tier = 2;
					brick[brickPos + l].x += Hspace;
					brick[brickPos + l].y += Vspace;
					brick[brickPos + l].recMask.x = brick[brickPos + l].x;
					brick[brickPos + l].recMask.y = brick[brickPos + l].y;

					
					Hspace += 192;
					
				}
				
				Hspace = 0;
				brickPos += 5;
			}
			else if (row[i] == ALTERNATE) {

				for (int t = 0; t < 10; t++)

				{
					brick[brickPos + t].brickImage = Bricks[rand()%4 *4];
					brick[brickPos + t].color = rand() % 4 +1;
					brick[brickPos + t].tier = rand() % 3;
					brick[brickPos + t].x += Hspace;
					brick[brickPos + t].y += Vspace;
					brick[brickPos + t].recMask.x = brick[brickPos + t].x;
					brick[brickPos + t].recMask.y = brick[brickPos + t].y;

					
					Hspace += 96;
					
				}
				Hspace = 0;
				brickPos += 10;
				
				
			}

			counter++;
			Hspace = 0;
			Vspace += 48;
		}

		break;
	
	}
	return brick;
}