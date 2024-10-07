#include <raylib.h>
#include <unordered_map>
#include <string>
#include <math.h>

class SmallBee
{
    private:
        std::unordered_map<std::string, Texture2D> texture = 
        {
            {"fly", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Mob/Small Bee/Fly/Fly-Sheet.png")},
            {"attack", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Mob/Small Bee/Attack/Attack-Sheet.png")},
            {"hit", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Mob/Small Bee/Hit/Hit-Sheet.png")}
        };
    private:
        //animations
        int maxFrames{4};
        int frames{};
        std::unordered_map<std::string, float> updateTime = 
        {
            {"fly", 1.f/10.f},
            {"attack",1.f/10.f},
            {"hit", 1.f/10.f}
        };
        float runningTime;
        std::string current{"fly"};
    private:
        //parameters
        float winWidth;
        float winHeight;
        Vector2 screenPos{static_cast<float>(winWidth) - 300, static_cast<float>(winHeight - winHeight/3)};
        Vector2 worldPos{};
        float beeWidth{};
        float beeHeight{};
        const float scale{3};
        int direction{1};
        Rectangle collisionRec{};
        int HP{200};
        //movement
        float range{400};
        float currentRange{};
        int velocity{60};
        //enemy detection
        float detectionRange{300};
    public:
        SmallBee(float windowWidth, float windowHeight);
        void Tick(float deltaTime, float* targetPos, Rectangle* playerCollision, Rectangle* weaponCollision);
        void Draw(float deltaTime);
        void HitAnimationEnd();
        Rectangle GetEnemyCollision()
        {
            return collisionRec;
        }
};