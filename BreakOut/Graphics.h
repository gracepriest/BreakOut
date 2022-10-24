#pragma once
static Texture2D BACKGROUND;
static Texture2D MAIN;
static Texture2D HEARTS;

static void InitGraphics()
{
	 BACKGROUND = LoadTexture("graphics/background.png");
	 MAIN = LoadTexture("graphics/breakout.png");
	//const Texture2D ARROWS = LoadTexture("graphics/arrows.png");
	 HEARTS = LoadTexture("graphics/hearts.png");
	//const Texture2D PARTICLE = LoadTexture("graphics/particle.png");
}
