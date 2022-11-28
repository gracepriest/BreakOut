#include "Game.h"

#include "Console.h"




////DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
//DrawTextEx(basicFont, "Congrats! You created your first window!", Vector2{50,200},MEDIUM,2,SKYBLUE);

int main()
{

    Console console;
    console.HideConsole();

    Game GameApp;

    GameApp.Start();


    return 0;
}
