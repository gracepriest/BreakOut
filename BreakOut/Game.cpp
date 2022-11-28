
#include "Game.h"
#include "States.h"

#include "Fonts.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Heart.h"



static State SceneManager;
std::vector<Texture2D> Hearts;

bool IsRunning = true;

Sound mySound;

extern float deltaTime;


void Init()
{
	if (SceneManager.getCurrrentState() == nullptr)
	{
		SceneManager.SetState(TitleState::getInstance());
	}
	else
	{
		SceneManager.Init();
	}
}

//Paddle player;

int Game::Load()
{

	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Break Out");
	InitAudioDevice();     // Initialize audio device

	srand(time(NULL));

	InitGraphics();
	InitSound();
	InitFont();
	InitPaddleQuad();
	InitBall();
	InitBrick();
	InitHeart();

	SceneManager.Init();
	
	
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	return 0;
}


void Game::Update()
{
	while (!WindowShouldClose())    // Detect window close button or ESC key windowshouldclose will be replaced by iskeypress
	{
		
			/*if (WindowShouldClose())
		{
			IsRunning = false;
		}*/
		
		deltaTime = GetFrameTime();
		SceneManager.Update();
		//player.Update(deltaTime);
		Draw(deltaTime);
		
	}
}

void Game::Draw(float dt)
{
	
	ClearBackground(RAYWHITE);
	BeginDrawing();
	float x = 250;
	int count = 0;
	
	//DrawTexture(BACKGROUND, 0, 0, WHITE);
	DrawTextureEx(BACKGROUND, { 0, 0 }, 0.0f, 5.7, WHITE);
	SceneManager.Render();
	DrawFPS(0, 0);
	EndDrawing();

}

void render()
{
	Image quad = LoadImageFromTexture(MAIN);

	Rectangle rec{ 0,0,32,16 };
	Image q2 = ImageFromImage(quad, rec);
	Texture2D text = LoadTextureFromImage(q2);
	rec = { 0,0,85,25 };
	DrawTextureQuad(text, Vector2{ 1,1 }, Vector2{ 0,0, }, rec, WHITE);
	//2
	//void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint);           // Draw a part of a texture defined by a rectangle with 'pro' parameters
	//DrawTexturePro(text, rec, Rectangle{ 0,0,75,20}, Vector2{-100,-50 }, 0, WHITE);
	//DrawTexture(text, 250, 100, WHITE);
	//DrawTextureEx(text, Vector2{ 50,100 },0, 1.5, WHITE);

	/*for (int i = 0; i < 4; i++)
	{
		DrawTexture(Paddles[i + count], x, 150, WHITE);
		count++;
		DrawTexture(Paddles[i + count], x, 200, WHITE);
		count++;
		DrawTexture(Paddles[i + count], x, 250, WHITE);
		count++;
		DrawTexture(Paddles[i + count], x, 300, WHITE);

		x += 150;
	}*/

}

void Game::Start()
{
	Load();
	Update();
}

 Game::~Game()
{
	CloseAudioDevice();
	
	CloseWindow();
}
