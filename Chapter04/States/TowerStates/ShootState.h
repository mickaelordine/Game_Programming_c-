#pragma once
#include "../AIState.h"
#include "../../Tower.h"
#include "../../Bullet.h"

class ShootState : public AIState
{
public:
    ShootState(class AIComponent* owner, class Tower* tower);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Shoot"; }
    void OnEnter() override;
    void OnExit() override;

private:
    Tower* mTower;
};
