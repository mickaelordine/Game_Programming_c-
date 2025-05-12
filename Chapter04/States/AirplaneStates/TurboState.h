#pragma once
#include <cstdlib>

#include "../AIState.h"

class TurboState : public AIState
{
public:
    TurboState(class AIComponent* owner, class NavComponent* nav_component);
    void Update(float deltaTime) override;
    const char* GetName() const override { return "Turbo"; }
    void OnEnter() override;
    void OnExit() override;

    NavComponent* nav_component;

private:
    float mTimeInState;
    float mTimeForNextState = rand()%2 + 1;
};
