// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.at(GetAnimationState()).size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;
		
		// Wrap current frame if needed
		while (mCurrFrame >= mAnimTextures.at(GetAnimationState()).size())
		{
			mCurrFrame -= mAnimTextures.at(GetAnimationState()).size();
		}

		// Set the current texture
		SetTexture(mAnimTextures.at(GetAnimationState())[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<std::vector<SDL_Texture*>>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.at(GetAnimationState()).size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures.at(GetAnimationState())[0]);
	}
}


void AnimSpriteComponent::SetAnimationState(AnimationState newstate)
{
	currentAnimSlot = newstate;
}