#include "Skeleton.h"

#include <iostream>

#include "AnimSpriteComponent.h"
#include "Game.h"



Skeleton::Skeleton(Game* game)
    :Actor(game)
    ,mRightSpeed(0.0f)
{
    // Create an animated sprite component
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    std::vector<std::vector<SDL_Texture*>> animationsSlots;
    std::vector<SDL_Texture*> movement = {
        game->GetTexture("Assets/Character01.png"),
        game->GetTexture("Assets/Character02.png"),
        game->GetTexture("Assets/Character03.png"),
        game->GetTexture("Assets/Character04.png"),
        game->GetTexture("Assets/Character05.png"),
        game->GetTexture("Assets/Character06.png"),
    };
    animationsSlots.push_back(movement);

    std::vector<SDL_Texture*> jump = {
        game->GetTexture("Assets/Character07.png"),
        game->GetTexture("Assets/Character08.png"),
        game->GetTexture("Assets/Character09.png"),
        game->GetTexture("Assets/Character10.png"),
        game->GetTexture("Assets/Character11.png"),
        game->GetTexture("Assets/Character12.png"),
        game->GetTexture("Assets/Character13.png"),
        game->GetTexture("Assets/Character14.png"),
        game->GetTexture("Assets/Character15.png"),
    };
    animationsSlots.push_back(jump);

    std::vector<SDL_Texture*> punch = {
        game->GetTexture("Assets/Character16.png"),
        game->GetTexture("Assets/Character17.png"),
        game->GetTexture("Assets/Character18.png"),
    };
    animationsSlots.push_back(punch);
    asc->SetAnimTextures(animationsSlots);
}

void Skeleton::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    
    // Update position based on speeds and delta time
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    // Restrict position to left half of screen
    if (pos.x < 25.0f)
    {
        pos.x = 25.0f;
    }
    else if (pos.x > 500.0f)
    {
        pos.x = 500.0f;
    }
    if (pos.y < 25.0f)
    {
        pos.y = 25.0f;
    }
    else if (pos.y > 743.0f)
    {
        pos.y = 743.0f;
    }
    SetPosition(pos);
}

void Skeleton::ProcessKeyboard(const uint8_t* state)
{
    // mRightSpeed = 0.0f;
    // // right/left
    // if (state[SDL_SCANCODE_D])
    // {
    //     mRightSpeed += 250.0f;
    //     this->GetComponent<AnimSpriteComponent>()->SetAnimationState(AnimSpriteComponent::moving);
    // }
    // if (state[SDL_SCANCODE_A])
    // {
    //     mRightSpeed -= 250.0f;
    //     this->GetComponent<AnimSpriteComponent>()->SetAnimationState(AnimSpriteComponent::moving);
    // }
    // // Jump
    // if (state[SDL_SCANCODE_W])
    // {
    //     mDownSpeed += 250.0f;
    //     this->GetComponent<AnimSpriteComponent>()->SetAnimationState(AnimSpriteComponent::jumping);
    // }
    // if (state[SDL_SCANCODE_S])
    // {
    //     mDownSpeed -= 250.0f;
    //     this->GetComponent<AnimSpriteComponent>()->SetAnimationState(AnimSpriteComponent::jumping);
    // }
    // //punch
    // if (state[SDL_SCANCODE_SPACE])
    // {
    //     this->GetComponent<AnimSpriteComponent>()->SetAnimationState(AnimSpriteComponent::punching);
    // }

    //here we need to add an idle animation state       
    
}


