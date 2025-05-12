#include "TurboState.h"

#include "../AIComponent.h"
#include "../../NavComponent.h"

TurboState::TurboState(class AIComponent* owner,  class NavComponent* mNavComp) : AIState(owner), mTimeInState(0.0f), nav_component(mNavComp)
{
    //set velocity here
    nav_component->SetForwardSpeed(0.0f);
}

void TurboState::Update(float deltaTime)
{
    mTimeInState += deltaTime;
    if (mTimeInState > mTimeForNextState)
    {
        mOwner->ChangeState("Rest");
    }
}

void TurboState::OnEnter()
{
    nav_component->SetForwardSpeed(230.0f);
}

void TurboState::OnExit()
{
    mTimeInState = 0.0f;
}
