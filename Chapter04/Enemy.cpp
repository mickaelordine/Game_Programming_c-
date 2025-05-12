// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

#include "States/AIComponent.h"
#include "States/AIState.h"
#include "States/AirplaneStates/MovingState.h"
#include "States/AirplaneStates/RestState.h"
#include "States/AirplaneStates/TurboState.h"

Enemy::Enemy(class Game* game)
:Actor(game)
{
	// Add to enemy vector
	game->GetEnemies().emplace_back(this);
	
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
	
	// Set position at start tile
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	
	// Setup a nav component at the start tile
	NavComponent* nc = new NavComponent(this);
	nc->SetForwardSpeed(150.0f);
	nc->StartPath(GetGame()->GetGrid()->GetStartTile());
	
	//adding all the states
	ai_component = new AIComponent(this);
	ai_component->RegisterState(new MovingState(ai_component,nc));
	ai_component->RegisterState(new TurboState(ai_component,nc));
	ai_component->RegisterState(new RestState(ai_component,nc));
	ai_component->ChangeState("Moving");
	
	// Setup a circle for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(GetGame()->GetEnemies().begin(),
						  GetGame()->GetEnemies().end(),
						  this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	// Am I near the end tile?
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		SetState(EDead);
	}
}
