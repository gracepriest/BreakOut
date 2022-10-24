#pragma once
#include <raylib.h>



 extern Sound HIT_PADDLE;
 extern Sound HURT;
 extern Sound HIT_BRICK_1;
 extern Sound HIT_BRICK_2;
 extern Sound PAUSE;
 extern Sound HIT_WALL;

void static InitSound()
{
	HIT_PADDLE = LoadSound("Sounds/paddle_hit.wav");
	//const Sound SCORE = LoadSound("Sounds/score.wav");
	 HIT_WALL = LoadSound("Sounds/wall_hit.wav");
	//const Sound CONFIRM = LoadSound("Sounds/confirm.wav ");
	//const Sound SELECT = LoadSound("Sounds/select.wav ");
	//const Sound NO_SELECT = LoadSound("Sounds/no-select.wav ");
	 HIT_BRICK_1 = LoadSound("Sounds/brick-hit-1.wav");
	 HIT_BRICK_2 = LoadSound("Sounds/brick-hit-2.wav");
	 HURT = LoadSound("Sounds/hurt.wav");
	//const Sound VICTORY = LoadSound("Sounds/victory");
	//const Sound RECOVER = LoadSound("Sounds/recover");
	//const Sound HIGH_SCORE = LoadSound("Sounds/high-score");
	  PAUSE = LoadSound("Sounds/pause.wav");
	//const Sound MUSIC = LoadSound("Sounds/music");
}


