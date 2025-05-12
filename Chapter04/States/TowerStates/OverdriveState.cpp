#include "OverdriveState.h"

#include "../AIComponent.h"
#include "../../Tower.h"

OverdriveState::OverdriveState(class AIComponent* owner, Tower* tower) : AIState(owner), mTower(tower)
{
    
}

void OverdriveState::Update(float deltaTime)
{
    mTimePassed += deltaTime;
    if (mTimePassed >= mShootSpeed)
    {
        if (mTower->GetAmmo() > 0)
        {
            Bullet* b = new Bullet(mTower->GetGame());
            b->SetPosition(mTower->GetPosition());
            b->SetRotation(mTower->GetRotation());
            mTower->SetAmmo(mTower->GetAmmo() - 1);
        }else
        {
            mOwner->ChangeState("Idle");
        }
        mTimePassed = 0.0f;
    }
}

void OverdriveState::OnEnter()
{
    mTower->SetAmmo(5);
}

void OverdriveState::OnExit()
{
    mTimePassed = 0.0f;
}