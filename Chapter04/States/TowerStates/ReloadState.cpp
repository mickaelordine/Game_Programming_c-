#include "ReloadState.h"

#include "../AIComponent.h"
#include "../../Tower.h"

ReloadState::ReloadState(class AIComponent* owner, class Tower* tower) : AIState(owner), mTower(tower)
{
    
}

void ReloadState::Update(float deltaTime)
{
    mReloadTime += deltaTime;
    if (mReloadTime >= 5.0f)
    {
        mOwner->ChangeState("Idle");
    }
}

void ReloadState::OnEnter()
{
    mTower->SetAmmo(5);
}

void ReloadState::OnExit()
{
    
}