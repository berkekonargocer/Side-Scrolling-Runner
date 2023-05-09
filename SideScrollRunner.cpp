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


int main()
{
	const auto* game = new Game();
	auto* rectangle = new RectangleObject();

	InitWindow(game->SCREEN_WIDTH, game->SCREEN_HEIGHT, "Side Scroll Runner");
	SetTargetFPS(144);

	// ----------------------------------------- RUNNER BOY INIT --------------------------------------

	Texture2D RBoyTexture2D = LoadTexture("Textures/RunnerBoy.png");
	Vector2 RunnerBoyPosition;
	Rectangle RBoyRectangle;

	const float RunnerBoyMovementSpeed = 10;
	const float RunnerBoyJumpVelocity = -15;
	float Velocity_Y = 0;

	RBoyRectangle.width = RBoyTexture2D.width / 6;
	RBoyRectangle.height = RBoyTexture2D.height;

	RBoyRectangle.x = 0;
	RBoyRectangle.y = 0;

	RunnerBoyPosition.x = game->SCREEN_WIDTH / 4 - RBoyRectangle.width / 2;
	RunnerBoyPosition.y = game->SCREEN_HEIGHT - RBoyRectangle.height;
	// ------------------------------------------------------------------------------------------------

	// ------------------------------------------ GAME LOOP START -------------------------------------
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// ------------------------------------- GAME LOGIC START -------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const float runnerBoyUpperYEdge = RunnerBoyPosition.y;
		const float runnerBoyBottomYEdge = RunnerBoyPosition.y;
		const float runnerBoyRightXEdge = RunnerBoyPosition.x;
		const float runnerBoyLeftXEdge = RunnerBoyPosition.x;
		// --------------------------------------------------------------------------------------------


		// ----------------------------------- SET RECTANGLE EDGES ------------------------------------
		const bool isOnTop = runnerBoyUpperYEdge <= 0;
		const bool isOnBottom = runnerBoyBottomYEdge >= game->SCREEN_HEIGHT - RBoyRectangle.height;
		const bool isOnRightEdge = runnerBoyRightXEdge >= game->SCREEN_WIDTH - RBoyRectangle.width;
		const bool isOnLeftEdge = runnerBoyLeftXEdge <= 0;
		// --------------------------------------------------------------------------------------------


		// ------------------------------------- MOVEMENT INPUTS --------------------------------------
		if (IsKeyDown(KEY_A) && !isOnLeftEdge)
		{
			RunnerBoyPosition.x -= RunnerBoyMovementSpeed;
		}
		if (IsKeyDown(KEY_D) && !isOnRightEdge)
		{
			RunnerBoyPosition.x += RunnerBoyMovementSpeed;
		}
		// --------------------------------------------------------------------------------------------

		// ------------------------------ GROUNDED CHECK AND ADD GRAVITY ------------------------------
		if (isOnBottom)
		{
			Velocity_Y = 0;
		}
		else
		{
			Velocity_Y += game->gravity;
		}
		// --------------------------------------------------------------------------------------------

		// --------------------------------------- JUMP INPUT -----------------------------------------
		if (IsKeyPressed(KEY_SPACE) && isOnBottom)
		{
			
			Velocity_Y += RunnerBoyJumpVelocity;
		}
		// --------------------------------------------------------------------------------------------

		// --------------------------------- APPLY VERTICAL VELOCITY ----------------------------------
		RunnerBoyPosition.y += Velocity_Y;
		// --------------------------------------------------------------------------------------------


		DrawTextureRec(RBoyTexture2D, RBoyRectangle, RunnerBoyPosition, WHITE);

		// ------------------------------------- GAME LOGIC END ---------------------------------------


		EndDrawing();
	}
	// ----------------------------------------- GAME LOOP END ----------------------------------------
	UnloadTexture(RBoyTexture2D);
	CloseWindow();
}