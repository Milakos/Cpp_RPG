#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, " TopDown");

    Texture2D map = LoadTexture("nature_tileset/OpenWorld.png");
    Vector2 mapPos{0, 0};
    const float mapScale{4.0f};

    Character knight{windowWidth, windowHeight};
    

    Prop props[2]
    {
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
    };
    
    Enemy goblin{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime {Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};
    
    Enemy* enemies[]
    {
        &goblin, & slime
    };

    for (auto enemy : enemies)
    {
        enemy-> setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTexture(map, mapPos.x, mapPos.y, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }
        
        if(!knight.getAlive())
        {
            DrawText("Game Over!" , 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        
        if (knight.getWorldPos().x < 0.f 
            || knight.getWorldPos().y < 0.f 
            || knight.getWorldPos().x + windowWidth > map.width * mapScale 
            || knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.UndoMovement();
        }       
        for (auto prop : props)
        {
           if(CheckCollisionRecs(prop.getCollidionRec(knight.getWorldPos()), knight.GetCollisionRec()))
           {
                knight.UndoMovement();
           }
        }
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->GetCollisionRec(), knight.GetCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }

        }
        
        EndDrawing();
    }
    CloseWindow();
}