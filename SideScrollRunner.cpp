#include <iostream>
#include  "raylib.h"

class Game
{
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
};

int main()
{
	const auto* game = new Game();

	InitWindow(game->SCREEN_HEIGHT, game->SCREEN_WIDTH, "Side Scroll Runner");

	while(WindowShouldClose() == false)
	{
		
	}

}