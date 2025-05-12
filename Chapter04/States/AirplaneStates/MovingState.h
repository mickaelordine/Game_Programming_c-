#pragma once
#include <cstdlib>

#include "../AIState.h"

class MovingState : public AIState
{
public:
    MovingState(class AIComponent* owner, class NavComponent* nav_component);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Moving"; }
    void OnEnter() override;
    void OnExit() override;

    NavComponent* nav_component;

private:
    float mTimeInState;
    float mTimeForNextState = rand() % 10 + 1;
};
