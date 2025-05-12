// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Tower : public Actor
{
public:
	Tower(class Game* game);
	void UpdateActor(float deltaTime) override;
	class AIComponent* ai_component;
	int GetAmmo() { return ammo; }
	void SetAmmo(int p_ammo) { this->ammo = p_ammo; }
	
private:
	class MoveComponent* mMove;
	float mNextAttack;
	int ammo = 5;
};
