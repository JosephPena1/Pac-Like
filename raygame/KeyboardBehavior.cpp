#include "KeyboardBehavior.h"
#include "raylib.h"
#include <Vector2.h>

void KeyboardBehavior::update(Agent* owner, float deltaTime)
{
    if (IsKeyDown(KEY_W))
        owner->setVelocity({ 0.0f, -m_speedIncrement });
    if (IsKeyDown(KEY_S))
        owner->setVelocity({ 0.0f, m_speedIncrement });
    if (IsKeyDown(KEY_A))
        owner->setVelocity({ -m_speedIncrement, 0.0f });
    if (IsKeyDown(KEY_D))
        owner->setVelocity({ m_speedIncrement, 0.0f });
    if (IsKeyDown(KEY_LEFT_CONTROL))
        owner->setVelocity({0, 0});
}
