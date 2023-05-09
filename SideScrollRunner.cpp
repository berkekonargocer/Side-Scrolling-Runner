#include <iostream>
#include  "raylib.h"

class RectangleObject
{
public:
	int Width = 20;
	int Height = 30;
	int CurrentXPosition = 640;
	int CurrentYPosition = 720 - Height;
	Color ObjectColor{ PURPLE };
	int MovementSpeed = 10;
	float JumpVelocity = -15;
	float Velocity_Y = 0;
};

class Game
{
public:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const float gravity = 0.5f;
};

class RunnerBoy
{
public:
	Texture2D RBoyTexture2D = LoadTexture("Textures/RunnerBoy");
	Vector2 Position;
	Rectangle RBoyRectangle;

	int MovementSpeed = 10;
	float JumpVelocity = -15;
	float Velocity_Y = 0;

};

int main()
{
	auto* runnerBoy = new RunnerBoy();
	const auto* game = new Game();
	auto* rectangle = new RectangleObject();

	InitWindow(game->SCREEN_WIDTH, game->SCREEN_HEIGHT, "Side Scroll Runner");
	SetTargetFPS(144);

	// ----------------------------------------- RUNNER BOY INIT --------------------------------------
	runnerBoy->RBoyRectangle.width = runnerBoy->RBoyTexture2D.width / 6;
	runnerBoy->RBoyRectangle.height = runnerBoy->RBoyTexture2D.height;

	runnerBoy->RBoyRectangle.x = 0;
	runnerBoy->RBoyRectangle.y = 0;

	runnerBoy->Position.x = game->SCREEN_WIDTH / 4 - runnerBoy->RBoyRectangle.width / 2;
	runnerBoy->Position.y = game->SCREEN_HEIGHT;
	// ------------------------------------------------------------------------------------------------

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
			
			rectangle->Velocity_Y += rectangle->JumpVelocity;
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