#include <raylib.h>
#include "SmallBee.h"

SmallBee::SmallBee(float windowWidth, float windowHeight) : 
    winWidth(windowWidth),
    winHeight(windowHeight)
{

}

void SmallBee::Draw(float deltaTime)
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

    beeWidth = static_cast<float>(texture[current].width) / maxFrames;
    beeHeight = static_cast<float>(texture[current].height);

    Vector2 origin{};
    Rectangle currentSource{beeWidth * frames, 0.f, static_cast<float>(texture[current].width/maxFrames) * direction, beeHeight};
    Rectangle currentDest{screenPos.x, screenPos.y, static_cast<float>(texture[current].width/maxFrames) * scale, beeHeight * scale};
    DrawTexturePro(texture[current], currentSource, currentDest, origin, 0.f, WHITE);
}

void SmallBee::Tick(float deltaTime, float* targetPos, Rectangle* playerCollision, Rectangle* weaponCollision)
{
    float edge = 30;
    collisionRec = {screenPos.x + edge, screenPos.y + edge, beeWidth * scale  - 2 * edge, beeHeight * scale - 2 * edge};
    DrawRectangleLines(collisionRec.x, collisionRec.y, collisionRec.width, collisionRec.height, BLUE);

    if(CheckCollisionRecs(*weaponCollision, collisionRec))
    {
        if(current != "hit")
        {
            frames = 0;
            HP -= 25;
        }
        current = "hit";
    }
    HitAnimationEnd();
    //attacking the player if in range
    if(current != "hit")
    {
        if(abs(*targetPos - screenPos.x) <= detectionRange)
        {
            current = "attack";
            if(*targetPos < screenPos.x)
                direction = 1;
            else
                direction = -1;
            screenPos.x -= velocity * 2 * deltaTime * direction;
        }
        //flying in range
        else
        {
            if(currentRange >= range)
            {
                currentRange = 0;
                direction *= -1;
            }
            current  = "fly";
            currentRange += velocity * deltaTime;
            screenPos.x -= velocity * deltaTime * direction;
        }
    }
    
    if(HP > 0)
        Draw(deltaTime);
    else
        collisionRec = {};

}

void SmallBee::HitAnimationEnd()
{
    if(current == "hit" && frames < maxFrames-1)
    {
        current = "hit";
    }
    else
        current = "attack";
}