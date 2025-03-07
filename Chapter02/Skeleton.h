#pragma once
#include <cstdint>

#include "Actor.h"

class Skeleton : public Actor
{
public:
    Skeleton(Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
private:
    float mRightSpeed;
    float mDownSpeed;
};
