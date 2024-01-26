/**
 * @file main.cpp
 * @author Cristian Nieto (chriztheanvill@gmail.com)
 * @brief Just a Game
 * @version 0.1
 * @date 2021-02-09
 *
 * @copyright Copyright (c) 2024
 *
 */

// NOTE
// DONE
// WARNING
// BUG
// ERROR
// FIXME
// TODO(cris):

/* NOTE to check the program process:
	# Glances
	## Simple
	## glances -612 -t 0.5 -f name:.*program_name*
	## With left panel
	## glances -61 -t 0.5 -f name:.*program_name*
	### Shortcuts:
		q = exit

	# htop
	# htop --filter=program_name
		f10 = exit
*/

#include <fmt/color.h>
#include <raylib.h>
#include "src/Game.hpp"
#include "src/Colors.hpp"
#include <iostream>

double lastUpdateTime { };

auto EventTriggered(const double& interval) -> bool
{
	auto currentTime = GetTime( );
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) -> int
{
	const int screenWidth = 500;
	const int screenHeight = 620;
	const int FPS = 60;

	Color blueDark = { 44, 44, 127, 255 };

	InitWindow(screenWidth, screenHeight, "My Tetris");
	SetTargetFPS(FPS);

	Font font = LoadFontEx("assets/fonts/arial.ttf", 64, nullptr, 0);

	Game game;

	while (!WindowShouldClose( ))	// Detect window close button or ESC key
	{
		// Input
		game.HandleInput( );
		if (EventTriggered(.2)) game.MoveBlockDown( );
		// Update
		UpdateMusicStream(game.m_music);

		// Draw
		BeginDrawing( );

		ClearBackground(blueDark);

		DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE);
		DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
		if (game.m_gameOver)
			DrawTextEx(font, "GameOver!!!", { 320, 450 }, 38, 2, WHITE);

		float rectangleWidth { 170 };

		DrawRectangleRounded(
		  { 320, 55, rectangleWidth, 60 },
		  0.3,
		  6,
		  Utils::blueLight
		);

		char scoreText[10];
		sprintf(scoreText, "%d", game.m_score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

		DrawTextEx(
		  font,
		  scoreText,
		  { 320 + (rectangleWidth - textSize.x) / 2, 65 },
		  38,
		  2,
		  WHITE
		);
		DrawRectangleRounded(
		  { 320, 215, rectangleWidth, 180 },
		  0.3,
		  6,
		  Utils::blueLight
		);

		game.Draw( );

		EndDrawing( );
	}

	CloseWindow( );	  // Close window and OpenGL context

#ifdef NDEBUG
	fmt::print("\n\n RELEASE!\n");
#else
	fmt::print("\n\n Debug!\n");
#endif

	return 0;
}
