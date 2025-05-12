#pragma once
#include <cstdlib>

#include "../AIState.h"

class RestState : public AIState
{
public:
    RestState(class AIComponent* owner,class NavComponent* nav_component);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Rest"; }
    void OnEnter() override;
    void OnExit() override;

    NavComponent* nav_component;

private:
    float mTimeInState;
    float mTimeForNextState = rand()%1;
};
