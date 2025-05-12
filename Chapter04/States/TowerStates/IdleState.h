#pragma once
#include "../AIState.h"
#include "../../Game.h"
#include "../../Enemy.h"
#include "../../Bullet.h"
#include "../../Tower.h"

class IdleState : public AIState
{
public:
    IdleState(class AIComponent* owner, class Tower* tower);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Idle"; }
    void OnEnter() override;
    void OnExit() override;

private:
    Tower* mTower;
    float mNextAttack;
    const float AttackTime = 1.0f;
    const float AttackRange = 100.0f;
    
};
