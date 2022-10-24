#include "State.h"
#include "States.h"
#include "Graphics.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Heart.h"
#include "Particle.h"

using namespace std;

//Sounds
Sound HIT_PADDLE;
Sound HURT;
Sound HIT_BRICK_1;
Sound HIT_BRICK_2;
Sound PAUSE;
Sound HIT_WALL;
//Font
Font basicFont;
//player
Paddle player;
//ball
Ball ball;
vector<Texture2D> Balls;
//brick
vector<Brick> brick;
vector<Texture2D> Bricks;
//heart
vector<Heart> heart; 

//global dt
float deltaTime;

//playstate variable
bool isPause = false;
Particle particle[50];

//enterState variable
vector<string> scorelist(21);


char character[] = { 65,65,65 };

void TitleState::Init()
{
	//InitSound();
	//InitFont();
	heart = createHeartMap();
	currentLevel = 1;
	args.health = 3;
	args.score = 0;
	args.currentScore = 0;
	
	
}
void TitleState::Exit()
{

}
void TitleState::Render()
{
	DrawTextEx(basicFont, "BREAKOUT", Vector2{ 350, 250}, XXLARGE, 4, WHITE);
	
	Color tarBlue = WHITE;
	if (highLighted == 1)
	{
		tarBlue = Color{ 103, 255, 255, 255 };
	}
	else
	{
		tarBlue = WHITE;
	}
	DrawText("START", 550, 550, LARGE, tarBlue);
     if (highLighted == 2)
	{
		tarBlue = Color{ 103, 255, 255, 255 };
	}
	 else
	 {
		 tarBlue = WHITE;
	 }
	 DrawText("HIGH SCORE", 550, 550+35, LARGE, tarBlue);
	
	
}
void TitleState::Update(State& state)

{   
	
	
	
	if (IsKeyPressed(KEY_UP) or IsKeyPressed(KEY_DOWN))
	{
		
		highLighted++;
		if (highLighted > 2)
		{
			highLighted = 1;
		}
		PlaySound(HIT_PADDLE);
		
	}
	if (highLighted == 1 and IsKeyPressed(KEY_ENTER))
	{
		state.SetState(ServeState::getInstance(),args);
		state.Init();
		
	}
	if (highLighted == 2 and IsKeyPressed(KEY_ENTER))
	{
		args.score = 455;
		state.SetState(EnterScoreState::getInstance(), args);
		state.Init();

	}
	
	
}
BaseState& TitleState::getInstance()
{
	static TitleState singleton;
	return singleton;
}

void ServeState::Init()
{
	
	
	ball.Reset();
	player.Reset();
	
}
void ServeState::Exit()
{

}
void ServeState::Render()
{
	string strScore = "LEVEL " + to_string(LEVEL);

	DrawText(strScore.c_str(), 300, WINDOW_HEIGHT / 4, EXLARGE, WHITE);
	DrawText("Press Enter To Began", 300, WINDOW_HEIGHT / 2, EXLARGE, WHITE);
	player.Render();
	ball.Render();
	/*for (auto i : brick)
	{
		i.Render();
	}*/
}
void ServeState::Update(State& state)
{
	if (IsKeyPressed(KEY_ENTER))
	{

		state.SetState(PlayState::getInstance(),args);
		state.Init();
	}
}
BaseState& ServeState::getInstance()
{
	static ServeState singleton;
	return singleton;
}

void PlayState::Init()
{ 
	
	//ball.dx = random number between 150 and 200
	//ball.dy = random number between 150 and 200
	ball.dx = (rand() % 50) + 100;
	ball.dy = (rand() % 50) + 100;

	args.levelScore = Load(LEVEL);

}
void PlayState::Render()
{
	string strScore = "Score: " + to_string(args.score);
	
	if (isPause == true)
	{
		DrawText("PAUSED", 500, WINDOW_HEIGHT / 2,EXLARGE, WHITE);
	}
	DrawText(strScore.c_str(), 900, 0, LARGE, WHITE);
	player.Render();
	ball.Render();
	
	for (auto & i : heart)
	{
		i.Render();
	}
	for (auto & i : brick) 
	{
		i.Render();
	}

	for (auto& item : particle)
	{
		item.Render();
	}


}
void PlayState::Exit()
{

}
BaseState& PlayState::getInstance()
{
	static PlayState singleton;
	return singleton;
}
void PlayState::Update(State& state) // scene logic
{
	vector<Brick>::iterator ptr;
	if (IsKeyPressed(KEY_SPACE) and isPause == false)
	{
		isPause = true;
		PlaySound(PAUSE);
	}
	else if (IsKeyPressed(KEY_SPACE) and isPause == true)
	{
		isPause = false;
		PlaySound(PAUSE);
	}
	if (!isPause)
	{
		player.Update(deltaTime);
		ball.Update(deltaTime);
		for (auto& item : particle)
		{
		 item.Update(deltaTime);
		}
		if (ball.Collides(player))
		{
			//raise ball above paddle in case it goes below it, then reverse dy
			ball.y = player.y - ball.height;
			ball.dy = -ball.dy;
			//if we hit the paddle on the left, set dx to negative
			//if we hit the paddle on the right, set dx to positive
			if (ball.x < player.x + (player.width / 2) and player.dx < 0)
			{
				ball.dx = -150 + -(player.x + player.width / 2 - ball.x);
			}
			else if (ball.x > player.x + (player.width / 2) and player.dx > 0)
			{
				ball.dx = 150 + abs(player.x + player.width / 2 - ball.x);
			}

			PlaySound(HIT_PADDLE);
		}

		//collision code for bricks
		//we check to see if the opposite side of our velocity is outside of the brick;
		// if it is, we trigger a collision on that side. else we're within the X + width of
		//the brick and should check to see if the top or bottom edge is outside of the brick,
		//colliding on the top or bottom accordingly
		//left edge; only check if we're moving right, and offset the check by a couple of pixels
		//so that flush corner hits register as Y flips, not X flips
		for (ptr = brick.begin(); ptr != brick.end(); ptr++)
		{
			if (ptr->inPlay and ball.Collide(*ptr))
			{
				for (auto& item : particle)
				{
					switch (ptr->color)
					{
					case 1:
						item.color = BLUE;
						break;
					case 2:
						item.color = GREEN;
						break;
					case 3:
						item.color = RED;
						break;
					case 4:
						item.color = PURPLE;
						break;
					}
					item.position = Vector2{ ptr->x,ptr->y };
					item.active = true;
					item.alpha = 255;



				}
				ptr->Hit();
				
				
										
					//left edge; only check if we moving right
				 if (ball.recMask.x + 2  < ptr->recMask.x  and ball.dx > 0)
				 {
						//flip x velocity and reset position outside of brick
				
						ball.dx = -ball.dx;
						ball.x = ptr->recMask.x - ball.recMask.width;
				 } 
				//right edge;
				//check if we moving left
				else if (ball.recMask.x +6 > ptr->recMask.x + ptr->recMask.width and ball.dx < 0)
				{
					//if()
					//flip x velo and reset pos outside the brick
					ball.dx = -ball.dx;
					ball.x = ptr->recMask.x + ptr->recMask.width;
				}
			//top
				else if (ball.recMask.y < ptr->recMask.y)
				{
					ball.dy = -ball.dy;
					ball.y = ptr->recMask.y - ball.recMask.width;
				}
			//bottom
				else if (ball.recMask.y > ptr->recMask.y)
				{
					ball.dy = -ball.dy;
					ball.y = ptr->recMask.y + ptr->recMask.height;
			    }
				//add speed
				 if(ball.dy <500 and ball.dy > -500)
				 ball.dy *= 1.06;
				
				 //remove the brick from the vector
				 if (ptr->inPlay == false)
				 {
					ptr = brick.erase(ptr);
					args.currentScore++;
					args.score++;
					PlaySound(HIT_BRICK_1);
				 }
				 else
				 {
					 PlaySound(HIT_BRICK_2);
				 }
				 break;
			}
		
		}

	}
	if (ball.recMask.y >= WINDOW_HEIGHT)
	{
		heart[args.health-1].inPlay = false;
		args.health--;
		PlaySound(HURT);
		
		if (args.health <= 0)
		{
			state.SetState(GameOverState::getInstance(),args);
			state.Init();
		}
		else
		{
			state.SetState(ServeState::getInstance(),args);
			state.Init();
		}
	}
	if (args.currentScore == args.levelScore)
	{
		currentLevel++;
		args.currentScore = 0;
		args.levelScore = 0;
		for (auto& item : particle)
		{
			item.active = false;
		}
		state.SetState(ServeState::getInstance(), args);
		state.Init();
	}
}
int PlayState::Load(int& level)
{
	if (level < currentLevel)
	{
		level = currentLevel;
		brick = createMap(currentLevel);
	}
	return brick.size();
}

		
void GameOverState::Init()
{
	
	fstream FileHandler("Game.txt");
	string savedScore;
	int counter = 0;
	string scorekeeper;

	const int maxScore = 20;
	for (int i = 0; i < maxScore; i++)
	{
		if (getline(FileHandler, savedScore))
			scorelist[i] = savedScore;
	}

	

	for (int i=0;i<maxScore;i++)
	{
		if (counter % 2 == 1)
		{
			
			if (args.score > stoi(scorelist[i]))
			{

				enterscoreFlag = true;
			break;
			}
			counter++;
		}
		else
		{
			counter++;
		}
	}
	FileHandler.close();
}
void GameOverState::Exit()
{

}
void GameOverState::Render()
{
	string strScore = to_string(args.score);
	DrawText("GAME OVER ", 250, WINDOW_HEIGHT / 4, EXLARGE,BLUE);
	DrawText("YOUR SCORE IS: ", 250, WINDOW_HEIGHT / 3 +50, EXLARGE, RED);
	DrawText(strScore.c_str(), 800, WINDOW_HEIGHT/3 +50, EXLARGE, RED);
	DrawText("Press Enter To ", 250, WINDOW_HEIGHT / 2 +50, EXLARGE, SKYBLUE);
	DrawText("Replay Or ESC To End", 250, WINDOW_HEIGHT / 1.5, EXLARGE,SKYBLUE);
}
void GameOverState::Update(State& state)
{
	if (enterscoreFlag == false)
	{
		if (IsKeyPressed(KEY_ENTER))
	    {
			args.score = 0;
			args.health = 3;

			for (auto & i : heart)
			{
				i.inPlay = true;
			}
			LEVEL = 0;
		
			state.SetState(TitleState::getInstance(),args);
			state.Init();
	    }
	}
	else
	{
		LEVEL = 0;
		enterscoreFlag = false;
		state.SetState(EnterCharState::getInstance(), args);
		state.Init();
		
		
	}
}
BaseState& GameOverState::getInstance()
{
	static GameOverState singleton;
	return singleton;
}


void  EnterScoreState::Init()
{
	
	fstream FileHandler("Game.txt");
	string savedScore;
	

	const int maxScore = 20;
	for (int i = 0; i < maxScore; i++)
	{
		if (getline(FileHandler, savedScore))
			scorelist[i] = savedScore;
		
		
	}


	 

	FileHandler.close();
}
void  EnterScoreState::Exit() {}
void  EnterScoreState::Update(State& state) 
{
	if ( IsKeyPressed(KEY_ENTER))
	{
		state.SetState(TitleState::getInstance(), args);
		state.Init();
	}
}
void  EnterScoreState::Render() 
{
	int y = 0;
	int x = 550;
	int j = 1;
	DrawText("HIGH SCORES", 400, 100, EXLARGE, WHITE);
	for (int i = 0; i < 20; i++)
	{
		
		DrawText(scorelist[i].c_str(), x, 250 + y, LARGE, WHITE);
		if (i % 2 == 1)
		{
			DrawText(to_string(j).c_str(), x - 300, 250 + y, LARGE, WHITE);
			y += 35;
			x = 550;
			j++;
		}
		else
		{
			x +=150;
		}
		
	}

	DrawText("Press Enter To Return To Main Menu", 400, 650, MEDIUM, WHITE);
	
}
BaseState& EnterScoreState::getInstance() 
{
	static EnterScoreState singleton;
	return singleton;
}


void  EnterCharState::Init()

{
	
	fstream FileHandler("Game.txt");
	string savedScore;
	
	

	const int maxScore = 20;
	for (int i = 0; i < maxScore; i++)
	{
		if (getline(FileHandler, savedScore))
			scorelist[i] = savedScore;
		

	}

	FileHandler.close();

}
void  EnterCharState::Exit() {}
void  EnterCharState::Update(State& state)
{
	static int keylog = 0;
	int counter = 0;
	int scorekeeper =0;
	fstream FileHandler("Game.txt");
	
	



	if (IsKeyPressed(KEY_UP))
	{
		if(character[keylog] < 90)
		character[keylog] += 1;
	}
	else if(IsKeyPressed(KEY_DOWN) and character[keylog] > 65)
	{
		character[keylog] -= 1;
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		if(keylog <3)
		{
			keylog++;
			
		}
		else
		{
			//if current score is greater than scorelist replace it
			for (int i =0;i<scorelist.size();i++)
			{
				counter = i;
				if (counter % 2 == 1)
				{
					
					scorekeeper = stoi(scorelist[i].c_str());
					if (args.score >= scorekeeper)
					{
						scorelist[i - 1] = character;
						scorelist[i] = to_string(args.score);
						//write to file
						for (auto& item : scorelist)
						{
							//FileHandler.write(item.c_str(), item.size());
							FileHandler <<item<<endl;
						}
						break;
					}
				}
				else
				{

					counter++;
				}

			}
			keylog = 0;
			state.SetState(EnterScoreState::getInstance(), args);
			state.Init();
		}
		FileHandler.close();
	}
}
void  EnterCharState::Render()
{
	
	DrawText(&character[0], 550, 350, EXLARGE, WHITE);
	DrawText("Press Enter To Save ", 500, 450, LARGE, BLUE);
	
}
BaseState& EnterCharState::getInstance()
{
	static EnterCharState singleton;
	return singleton;
}

