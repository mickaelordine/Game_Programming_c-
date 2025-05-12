#pragma once
#include "../AIState.h"

class ReloadState : public AIState
{
public:
    ReloadState(class AIComponent* owner, class Tower* tower);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Reload"; }
    void OnEnter() override;
    void OnExit() override;

private:
    Tower* mTower;
    float mReloadTime;
    
};
