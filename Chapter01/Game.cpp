// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

#include <iostream>

const int thickness = 15;
const float paddleH = 100.0f;



Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mPaddleDir1(0)
,mPaddleDir2(1)
{
	
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//
	mPaddlePos1.x = 10.0f;
	mPaddlePos1.y = 768.0f/2.0f;
	mPaddlePos2.x = 1010.0f;
	mPaddlePos2.y = 768.0f/2.0f;
	
	//replace this with a Vector of 2||3 balls
	Ball* ball1 = new Ball();
	Ball* ball2 = new Ball();

	ball1->position.x = 1024.0f/2.0f;
	ball1->position.y = 768.0f/2.0f;
	ball1->velocity.x = 200.0f;
	ball1->velocity.y = 235.0f;
	ball2->position.x = 1024.0f/2.0f;
	ball2->position.y = 768.0f/2.0f;
	ball2->velocity.x = -200.0f;
	ball2->velocity.y = -235.0f;
	ballsVector.push_back(*ball1);
	ballsVector.push_back(*ball2);
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir1 = 0;
	mPaddleDir2 = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir1 -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir1 += 1;
	}
	if (state[SDL_SCANCODE_UP])
	{
		mPaddleDir2 -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		mPaddleDir2 += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle1 position based on direction
	if (mPaddleDir1 != 0)
	{
		mPaddlePos1.y += mPaddleDir1 * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos1.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos1.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos1.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos1.y = 768.0f - paddleH/2.0f - thickness;
		}
		
	}
	// Update paddle2 position based on direction
	if (mPaddleDir2 != 0)
	{
		mPaddlePos2.y += mPaddleDir2 * 300.0f * deltaTime;
		if (mPaddlePos2.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos2.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos2.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos2.y = 768.0f - paddleH/2.0f - thickness;
		}
	}
	
	//update balls pos based on velocity
	for (int i = 0; i<ballsVector.capacity(); i++)
	{
		ballsVector.at(i).position.x += ballsVector.at(i).velocity.x * deltaTime;
		ballsVector.at(i).position.y += ballsVector.at(i).velocity.y * deltaTime;
		// std::cout << "ball " << i << " posx: " << ballsVector.at(i).position.x << std::endl;
		// std::cout << "ball " << i << " posy: " << ballsVector.at(i).position.y << std::endl;
	}
	// Bounce if needed
	// Did we intersect with the paddle1?
	for (int i = 0; i<ballsVector.capacity(); i++)
	{
		float diff = mPaddlePos1.y - ballsVector.at(i).position.y;
		// Take absolute value of difference
		diff = (diff > 0.0f) ? diff : -diff;
		if (
			// Our y-difference is small enough
			diff <= paddleH / 2.0f &&
			// We are in the correct x-position
			ballsVector.at(i).position.x <= 25.0f && ballsVector.at(i).position.x >= 10.0f &&
			// The ball is moving to the left
			ballsVector.at(i).velocity.x < 0.0f)
		{
			ballsVector.at(i).velocity.x *= -1.0f; //switch the moving direction of the ball
		}
		// Did we intersect with the paddle2?
		float diff2 = mPaddlePos2.y - ballsVector.at(i).position.y;
		// Take absolute value of difference
		diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
		if (
			// Our y-difference is small enough
			diff2 <= paddleH / 2.0f &&
			// We are in the correct x-position for paddle 2
			ballsVector.at(i).position.x <= 1015.0f && ballsVector.at(i).position.x >= 1000.0f &&
			// The ball is moving to the right
			ballsVector.at(i).velocity.x > 0.0f)
		{
			ballsVector.at(i).velocity.x *= -1.0f; //switch the moving direction of the ball
		}
		// Did the ball go off the screen left? (if so, end game)
		else if (ballsVector.at(i).position.x <= 0.0f)
		{
			mIsRunning = false;
		}
		// Did the ball go off the screen right? (if so, end game)
		else if (ballsVector.at(i).position.x >= (1024.0f - thickness))
		{
			mIsRunning = false;
		}
			// Did the ball collide with the top wall?
		if (ballsVector.at(i).position.y <= thickness && ballsVector.at(i).velocity.y < 0.0f)
		{
			ballsVector.at(i).velocity.y *= -1;
		}
		// Did the ball collide with the bottom wall?
		else if (ballsVector.at(i).position.y >= (768 - thickness) &&
			ballsVector.at(i).velocity.y > 0.0f)
		{
			ballsVector.at(i).velocity.y *= -1;
		}
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 127, 127, 127, 127);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// color paddle1
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	// Draw paddle1
	SDL_Rect paddle1{
		static_cast<int>(mPaddlePos1.x),
		static_cast<int>(mPaddlePos1.y - paddleH/2),
		thickness-10,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle1);

	// color paddle2
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	// Draw paddle2
	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x),
		static_cast<int>(mPaddlePos2.y - paddleH/2),
		thickness-10,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	for (auto elem : ballsVector)
	{
		// color ball
		SDL_SetRenderDrawColor(mRenderer, static_cast<int>(elem.position.x), static_cast<int>(elem.position.x), static_cast<int>(elem.position.x), 255);
		// Draw ball
		SDL_Rect ball{	
			static_cast<int>(elem.position.x - thickness/2),
			static_cast<int>(elem.position.y - thickness/2),
			thickness-5,
			thickness-5
		};
		SDL_RenderFillRect(mRenderer, &ball);
	
		// Swap front buffer and back buffer
		SDL_RenderPresent(mRenderer);
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
