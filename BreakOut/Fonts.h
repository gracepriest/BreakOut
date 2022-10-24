#pragma once
#include <raylib.h>

static float SMALLFONT = 16;
static float MEDIUM = 24;
static float LARGE = 32;
static float EXLARGE = 64;
static float XXLARGE = 128;


static Font DEFAULT;
extern Font basicFont;

static void InitFont()
{
DEFAULT = GetFontDefault();
basicFont = LoadFont("Fonts/font.ttf");
}




