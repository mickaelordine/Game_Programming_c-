// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <SDL/SDL_stdinc.h>

#include "Actor.h"
class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
	void ResetLocationAndRotation();
	
	class CircleComponent* GetCircle() { return mCircle; }
	
private:
	float mLaserCooldown;
	class CircleComponent* mCircle;
	bool canBeDamaged = true;

	//functions
	void StartDelay(Uint32 milliseconds);
	void OnDelayComplete();

	//variable for delays
	bool isDelaying = false;
	Uint32 delayStartTime = 0;
	Uint32 delayDuration = 0;
};