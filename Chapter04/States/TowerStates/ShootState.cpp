#include "ShootState.h"
#include "../AIComponent.h"


ShootState::ShootState(class AIComponent* owner, class Tower* tower) : AIState(owner), mTower(tower)
{
    
}

void ShootState::Update(float deltaTime)
{
    
}

void ShootState::OnEnter()
{
    Bullet* b = new Bullet(mTower->GetGame());
    b->SetPosition(mTower->GetPosition());
    b->SetRotation(mTower->GetRotation());
    mTower->SetAmmo(mTower->GetAmmo() - 1);
    mOwner->ChangeState("Idle");
}

void ShootState::OnExit()
{
    
}