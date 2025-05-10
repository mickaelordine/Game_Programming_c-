// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"

#include <iostream>
#include <ostream>

#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner,  float mass, Vector2 constantForce, int updateOrder)
:Component(owner, updateOrder)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
, mVelocity(Vector2::Zero)
, mAccumulatedForce(Vector2::Zero)
, mMass(mass)
, mConstantForce(constantForce)
{
	
}

// void MoveComponent::Update(float deltaTime)
// {
// 	if (!Math::NearZero(mAngularSpeed))
// 	{
// 		float rot = mOwner->GetRotation();
// 		rot += mAngularSpeed * deltaTime;
// 		mOwner->SetRotation(rot);
// 	}
// 	
// 	if (!Math::NearZero(mForwardSpeed))
// 	{
// 		Vector2 pos = mOwner->GetPosition();
// 		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
// 		
// 		// (Screen wrapping code only for asteroids)
// 		if (pos.x < 0.0f) { pos.x = 1022.0f; }
// 		else if (pos.x > 1024.0f) { pos.x = 2.0f; }
//
// 		if (pos.y < 0.0f) { pos.y = 766.0f; }
// 		else if (pos.y > 768.0f) { pos.y = 2.0f; }
//
// 		mOwner->SetPosition(pos);
// 	}
// }

void MoveComponent::Update(float deltaTime)
{
	//friction
	AddForce(mVelocity * -2.0f);
	
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}
	
	if (!Math::NearZero(mMass))
	{
		Vector2 acceleration = Vector2(mAccumulatedForce.x / mMass, mAccumulatedForce.y / mMass);

		mVelocity += acceleration * deltaTime;

		Vector2 pos = mOwner->GetPosition();
		pos += mVelocity * deltaTime;

		//(Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
		
		
	}else
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		
		// (Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}

	if (!Math::NearZero(mConstantForce.x) || !Math::NearZero(mConstantForce.y))
	{
		Vector2 acceleration = Vector2(mConstantForce.x / mMass, mConstantForce.y / mMass);
		std::cout << mConstantForce.x << " " << mConstantForce.y << mOwner->GetGame() << std::endl;
		mVelocity += acceleration * deltaTime;

		Vector2 pos = mOwner->GetPosition();
		pos += mVelocity * deltaTime;

		//(Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}

	// Reset the accumulated force
	mAccumulatedForce = Vector2::Zero;
}

//function used for exercise 3.3
void MoveComponent::AddForce(Vector2 force)
{
	mAccumulatedForce += force;
}

