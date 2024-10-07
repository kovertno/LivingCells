/*#include <raylib.h>
#include "Enemy.h"

#ifndef ENEMY_H
#define ENEMY_H

Enemy::Enemy()
{

}

void Enemy::Tick(float deltaTime)
{
    Draw(deltaTime);
}

void Enemy::Draw(float deltaTime)
{
    runningTime += deltaTime;
    if(runningTime >= updateTime[current])
    {
        runningTime = 0;
        ++frames;
        if(frames >= maxFrames)
        {
            frames = 0;
        }
    }

    charWidth = static_cast<float>(texture[current].width) / maxFrames;
    charHeight = static_cast<float>(texture[current].height);

    Vector2 origin{};
    Rectangle currentSource{charWidth * frames, 0.f, static_cast<float>(texture[current].width/maxFrames) * leftRight, charHeight};
    Rectangle currentDest{screenPos.x, screenPos.y, static_cast<float>(texture[current].width/maxFrames) * scale, charHeight * scale};
    DrawTexturePro(texture[current], currentSource, currentDest, origin, 0.f, WHITE);
}

#endif*/