#include <raylib.h>
#include "Hero.h"

Hero::Hero(int windowWidth, int windowHeight) : 
    winWidth(windowWidth),
    winHeight(windowHeight)
{

}
//drawing the character
void Hero::Draw(float deltaTime)
{
    runningTime += deltaTime;
    if(runningTime >= updateTime[current])
    {
        runningTime = 0;
        if(current != "dead")
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

void Hero::Tick(float deltaTime)
{
    direction = {};
    float moveRecX = {};
    float moveRecY = {};
    float edges = 30;
    //inputs
    if(HP > 0)
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            if(isOnGround)
            {
                if(current != "attack")
                {
                    frames = 0;
                }
                weaponCollision = {screenPos.x, screenPos.y, (float)texture["attack"].width/8 * scale - 60, (float)texture["attack"].height * scale};
                current = "attack";
                maxFrames = 8;
                //screenPos.x += velocity * leftRight * deltaTime * 100;
            }
        }
        AtkAnimationEnd();
        if(current != "attack")
        {
            if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE))
            {
                if(isOnGround)
                {
                    direction.y = -1;
                    isOnGround = false;
                    verticalVel = -jumpVel;
                }
            }
            if(IsKeyDown(KEY_S))
            {
                
            }
            if(IsKeyDown(KEY_A))
            {
                direction.x = -1;
                leftRight = -1;
                if(isOnGround)
                {
                    current = "run";
                    maxFrames = 8;
                }
            }
            if(IsKeyDown(KEY_D))
            {
                direction.x = 1;
                leftRight = 1;
                if(isOnGround)
                {
                    current = "run";
                    maxFrames = 8; 
                }
            }
        }

        if(direction.x > 0 && isOnGround)
        {
            moveRecX = 50;
        }
        else if(!isOnGround)
        {
            moveRecY = 30;
        }
        playerCollision = {screenPos.x + moveRecX + edges, screenPos.y + edges - moveRecY, (float)texture["idle"].width/4 * scale - 2 * edges, (float)texture["idle"].height * scale - 2 * edges};

        //horizontal movement
        screenPos.x += velocity * direction.x * deltaTime * 30;

    DrawRectangleLines(playerCollision.x, playerCollision.y, playerCollision.width, playerCollision.height, RED);
    DrawRectangleLines(weaponCollision.x, weaponCollision.y, weaponCollision.width, weaponCollision.height, BLUE);

        //vertival movement and jump animaiton
        if(!isOnGround)
        {
            verticalVel += gravity * deltaTime * 4;
            current = "jump";
            maxFrames = 15;
        }

        screenPos.y += verticalVel * deltaTime * 15;

        if(screenPos.y >= ground)
        {
            isOnGround = true;     
            verticalVel = 0;
            screenPos.y = ground;
        }
    }
    else
    {
        
        if(screenPos.y >= ground)
        {
            isOnGround = true;
            verticalVel = 0;
            screenPos.y = ground;
        }
        screenPos.y += gravity * deltaTime * 32;
    }
    Draw(deltaTime);
}

void Hero::AtkAnimationEnd()
{
    if(current == "attack" && frames < maxFrames-1)
    {
        return;
    }
    else
    {
        if(HP > 0)
        {
            current = "idle";
            maxFrames = 4;
            weaponCollision = {};
        }
    }
}