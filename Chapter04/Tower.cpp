// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Tower.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "States/AIComponent.h"
#include "States/TowerStates/IdleState.h"
#include "States/TowerStates/OverdriveState.h"
#include "States/TowerStates/ReloadState.h"
#include "States/TowerStates/ShootState.h"

Tower::Tower(class Game* game)
:Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture("Assets/Tower.png"));
	
	mMove = new MoveComponent(this);
	//mMove->SetAngularSpeed(Math::Pi);

	//setting up state machine
	ai_component = new AIComponent(this);
	ai_component->RegisterState(new IdleState(ai_component, this));
	ai_component->RegisterState(new ShootState(ai_component, this));
	ai_component->RegisterState(new ReloadState(ai_component, this));
	ai_component->RegisterState(new OverdriveState(ai_component, this));
	ai_component->ChangeState("Idle");
	
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
}
