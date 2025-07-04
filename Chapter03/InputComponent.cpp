// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
:MoveComponent(owner, 2, Vector2::Zero)
,mForwardKey(0)
,mBackKey(0)
,mClockwiseKey(0)
,mCounterClockwiseKey(0)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		Vector2 force = mOwner->GetForward() * 200.0f; // mThrustForce tipo 100.0f
		AddForce(force);
	}
	if (keyState[mBackKey])
	{
		Vector2 force = mOwner->GetForward() * -150.0f; // mThrustForce tipo 100.0f
		AddForce(force);
	}
	SetForwardSpeed(forwardSpeed);

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
