#include <raylib.h>
#include "Hero.h"
#include "SmallBee.h"

int main()
{
    const int windowWidth{1200};
    const int windowHeight{700};

    InitWindow(windowWidth, windowHeight, "Living Cells");

    Hero hero(windowWidth, windowHeight);
    SmallBee bee1(windowWidth, windowHeight);

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        if(CheckCollisionRecs(hero.GetPlayerCollision(), bee1.GetEnemyCollision()))
        {

            hero.ChangeDeathString("dead");
            hero.ChangeMaxFrames(8);
        }

        hero.Tick(dT);
        bee1.Tick(dT, &hero.GetScreenPos().x, &hero.GetPlayerCollision(), &hero.GetWeaponCollision());

        EndDrawing();
    }
}