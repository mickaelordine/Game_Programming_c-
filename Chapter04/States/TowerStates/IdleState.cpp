#include "IdleState.h"
#include "../AIComponent.h"


IdleState::IdleState(class AIComponent* owner, Tower* tower) : AIState(owner), mTower(tower)
{
    
}

void IdleState::Update(float deltaTime)
{
    mNextAttack -= deltaTime;
    if (mNextAttack <= 0.0f)
    {
        Enemy* e = mTower->GetGame()->GetNearestEnemy(mTower->GetPosition());
        if (e != nullptr)
        {
            // Vector from me to enemy
            Vector2 dir = e->GetPosition() - mTower->GetPosition();
            float dist = dir.Length();
            if (dist < AttackRange)
            {
                // Rotate to face enemy
                mTower->SetRotation(Math::Atan2(-dir.y, dir.x));
                // Spawn bullet at tower position facing enemy
                if (rand() % 20 == 5)
                    mOwner->ChangeState("Overdrive");
                else
                    mOwner->ChangeState("Shoot");
            }
        }
        mNextAttack += AttackTime;
    }

    
}

void IdleState::OnEnter()
{
    if (mTower->GetAmmo() <= 0)
    {
        mOwner->ChangeState("Reload");
    }
}

void IdleState::OnExit()
{
    
}


