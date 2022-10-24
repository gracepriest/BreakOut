#include "Console.h"


#include <Windows.h>


Console::Console()
{

}
//handle closing and opening the console window
void Console::HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void Console::ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool Console::IsConsoleVisible()
{
    return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}
Console::~Console()
{

}