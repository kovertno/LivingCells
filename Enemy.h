/*#include <raylib.h>
#include <unordered_map>
#include <string>

class Enemy
{
    protected:
        //textures
        std::unordered_map<std::string, Texture2D> texture = {};
    protected:
        //animations
        float updateTime{};
        float runningTime{};
        int frame{};
        int maxFrames{};
        std::string current{};
    public:
        Enemy();
        virtual void Tick(float deltaTime);
        void Draw(float deltaTime);
};*/