#include <raylib.h>
#include <unordered_map>
#include <string>

class Hero
{
    private:
        //textures
        std::unordered_map<std::string, Texture2D> texture = 
        {
            {"idle", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Character/Idle/Idle-Sheet.png")},
            {"run", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Character/Run/Run-Sheet.png")},
            {"attack", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Character/Attack-01/Attack-01-Sheet.png")},
            {"jump", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Character/Jumlp-All/Jump-All-Sheet.png")},
            {"dead", LoadTexture("textures/Legacy-Fantasy - High Forest 2.3/Character/Dead/Dead-Sheet.png")}
        };
    private:
        //animations and parameters for the sprite
        float runningTime{};
        std::unordered_map<std::string, float> updateTime =
        {
            {"idle", 1.f/5.f},
            {"run", 1.f/15.f},
            {"attack", 1.f/15.f},
            {"jump", 1.f/9.f},
            {"dead", 1.f/15.f}
        };
        int frames{};
        int maxFrames{};
        int leftRight{1};
        const int scale{3};
        float charWidth{};
        float charHeight{};
        std::string current{};
        Rectangle weaponCollision{};
        Rectangle playerCollision{};
        int HP{500};
    private:
        //screen and world positions
        Vector2 direction{};
        int velocity{10};
        int winWidth{};
        int winHeight{};
        Vector2 screenPos{static_cast<float>(winWidth/8), static_cast<float>(winHeight - winHeight/3)};
        Vector2 worldPos{};
    private:
        //jumping
        float gravity{10};
        float verticalVel{};
        float jumpVel{40};
        float ground{static_cast<float>(winHeight - winHeight/3)};
        bool isOnGround{true};
    public:
        Hero(int windowWidth, int windowHeight);

        void Draw(float deltaTime);

        void Tick(float deltaTime);

        Vector2& GetScreenPos()
        {
            return screenPos;
        }

        Rectangle& GetPlayerCollision()
        {
            return playerCollision;
        }

        Rectangle& GetWeaponCollision()
        {
            return weaponCollision;
        }

        void ChangeDeathString(std::string death)
        {
            current = death;
            HP = 0;
        }

        void ChangeMaxFrames(int fr)
        {
            maxFrames = fr;
        }

        void AtkAnimationEnd();
};
