#pragma once
#include "../AIState.h"
#include "../../Bullet.h"

class OverdriveState : public AIState
{
public:
    OverdriveState(class AIComponent* owner, class Tower* tower);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Overdrive"; }
    void OnEnter() override;
    void OnExit() override;
    
private:
    Tower* mTower;
    float mTimePassed = 0.0f;
    const float mShootSpeed = 0.3f;
};
