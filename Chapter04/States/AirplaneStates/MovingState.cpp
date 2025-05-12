#include "MovingState.h"

#include "../AIComponent.h"
#include "../../NavComponent.h"

MovingState::MovingState(class AIComponent* owner,  class NavComponent* mNavComp) : AIState(owner), mTimeInState(0.0f), nav_component(mNavComp)
{
    //set velocity here
    nav_component->SetForwardSpeed(0.0f);
}

void MovingState::Update(float deltaTime)
{
    mTimeInState += deltaTime;
    if (mTimeInState > mTimeForNextState)
    {
        mOwner->ChangeState("Turbo");
    }
}

void MovingState::OnEnter()
{
    nav_component->SetForwardSpeed(150.0f);
}

void MovingState::OnExit()
{
    mTimeInState = 0.0f;
}


