#include "RestState.h"

#include "../AIComponent.h"
#include "../../NavComponent.h"

RestState::RestState(class AIComponent* owner,  class NavComponent* mNavComp) : AIState(owner), mTimeInState(0.0f), nav_component(mNavComp)
{
    //set velocity here
    nav_component->SetForwardSpeed(0.0f);
}

void RestState::Update(float deltaTime)
{
    mTimeInState += deltaTime;
    if (mTimeInState > mTimeForNextState)
    {
        mOwner->ChangeState("Moving");
    }
}

void RestState::OnEnter()
{
    nav_component->SetForwardSpeed(50.0f);
    
}

void RestState::OnExit()
{
    mTimeInState = 0.0f;
}
