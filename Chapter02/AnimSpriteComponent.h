// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	 enum AnimationState
	{
	 	moving,
	 	jumping,
	 	punching
	};
	
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overridden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::vector<std::vector<SDL_Texture*>>& textures);
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
	void SetAnimationState(AnimationState state);
	AnimationState GetAnimationState() const { return currentAnimSlot; }
private:
	// All textures in the animation
	std::vector<std::vector<SDL_Texture*>> mAnimTextures;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
	AnimationState currentAnimSlot = AnimationState::moving;
};
