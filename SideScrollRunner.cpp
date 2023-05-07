#include <iostream>
#include  "raylib.h"

class Game
{
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int gravity = 1.0f;
};

class RectangleObject
{
public:
	int Width = 20;
	int Height = 30;
	int CurrentXPosition = 640;
	int CurrentYPosition = 720 - Height;
	Color ObjectColor{ PURPLE };
	int MovementSpeed = 10;
	int Velocity_Y = 0;
};

int main()
{
	const auto* game = new Game();
	auto* rectangle = new RectangleObject();

	InitWindow(game->SCREEN_WIDTH, game->SCREEN_HEIGHT, "Side Scroll Runner");
	SetTargetFPS(144);


	// ------------------------------------------ GAME LOOP START -------------------------------------
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const int rectangleUpperYEdge = rectangle->CurrentYPosition;
		const int rectangleBottomYEdge = rectangle->CurrentYPosition + rectangle->Height;
		const int rectangleRightXEdge = rectangle->CurrentXPosition + rectangle->Width;
		const int rectangleLeftXEdge = rectangle->CurrentXPosition;
		// --------------------------------------------------------------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const bool isOnTop = rectangleUpperYEdge <= 0;
		const bool isOnBottom = rectangleBottomYEdge >= game->SCREEN_HEIGHT;
		const bool isOnRightEdge = rectangleRightXEdge >= game->SCREEN_WIDTH;
		const bool isOnLeftEdge = rectangleLeftXEdge <= 0;
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- MOVEMENT INPUTS --------------------------------------
		if (IsKeyDown(KEY_A) && !isOnLeftEdge)
		{
			rectangle->CurrentXPosition -= rectangle->MovementSpeed;
		}
		if (IsKeyDown(KEY_D) && !isOnRightEdge)
		{
			rectangle->CurrentXPosition += rectangle->MovementSpeed;
		}
		// --------------------------------------------------------------------------------------------

		// ------------------------------ GROUNDED CHECK AND ADD GRAVITY ------------------------------
		if (isOnBottom)
		{
			rectangle->Velocity_Y = 0;
		}
		else
		{
			rectangle->Velocity_Y += game->gravity;
		}
		// --------------------------------------------------------------------------------------------

		// --------------------------------------- JUMP INPUT -----------------------------------------
		if (IsKeyPressed(KEY_SPACE) && isOnBottom)
		{
			rectangle->Velocity_Y -= 20;
		}
		// --------------------------------------------------------------------------------------------

		// --------------------------------- APPLY VERTICAL VELOCITY ----------------------------------
		rectangle->CurrentYPosition += rectangle->Velocity_Y;
		// --------------------------------------------------------------------------------------------


		DrawRectangle(rectangle->CurrentXPosition, rectangle->CurrentYPosition, rectangle->Width, rectangle->Height, rectangle->ObjectColor);

		// ------------------------------------- GAME LOGIC END ---------------------------------------


		EndDrawing();
	}
	// ----------------------------------------- GAME LOOP END ----------------------------------------

	CloseWindow();
}