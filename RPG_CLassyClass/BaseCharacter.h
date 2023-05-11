#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter();
        Vector2 getWorldPos() { return worldPos; }
        void UndoMovement();
        Rectangle GetCollisionRec();
        virtual void tick(float deltaTime);
        virtual Vector2 getScreenPos() = 0;
        bool getAlive() {return alive;}
        void setAlive(bool isAlive){alive = isAlive;}
    protected:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        // Flip Direction
        float rightLeft = 1.0f;
        // Animation Variables
        float runningTime{};
        float frame{};
        int maxFrames = 6;
        float updateTIme{1.0 / 12.0f};
        float speed = 4.0f;
        float width{};
        float height{};
        float scale{4.0f};
        Vector2 velocity{};
    private:
        bool alive{true};
};


#endif