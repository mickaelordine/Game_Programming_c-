// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Game.h"
#include "Laser.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.0f)
	,mCircle(nullptr)
{
	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);
}

void Ship::OnDelayComplete()
{
	canBeDamaged = true;
}

void Ship::StartDelay(Uint32 milliseconds)
{
	isDelaying = true;
	delayStartTime = SDL_GetTicks();
	delayDuration = milliseconds;
}

void Ship::UpdateActor(float deltaTime)
{
	if (isDelaying)
	{
		Uint32 currentTime = SDL_GetTicks();
		if (currentTime - delayStartTime >= delayDuration)
		{
			isDelaying = false;
			OnDelayComplete();
		}
		return; // esce dall'update se in delay
	}
	
	mLaserCooldown -= deltaTime;
	// Do we intersect with an asteroid?
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			ast->SetState(EDead);
			ResetLocationAndRotation();
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
		
	}
}

void Ship::ResetLocationAndRotation()
{
	if (canBeDamaged)
	{
		canBeDamaged = false;
		this->SetPosition(Vector2(512.0f, 384.0f));
		this->SetRotation(Math::PiOver2);
		StartDelay(3000); 
	}
}

