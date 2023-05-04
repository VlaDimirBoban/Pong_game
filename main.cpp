#include "raylib.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>

int main(void)
{
    // Initialization

    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Ping Pong Bong");

    InitAudioDevice();

    int x = screenWidth / 2 - 50;
    int y = screenHeight / 2 - 150;

    int brzx;
    int brzy;

    // Initalization
    // int GetRandomValue(int min, int max);     // Get a random value between min and max (both included)

    // Daj loptici pocetnu brzinu
    // x, y pos + randomx.brz + randomy.brz

    // napravi sistem kolizije sa ivicama kadra
    // if RecCollision(loptica, ivica kadra){x, y pos + -randomx.brz + -randomy.brz}

    // loptica divlja do besvesti

    bool pravacx = false;
    bool pravacy = false;
    int velx = 0;
    int vely = 0;
    int frame = 0;
    float timer;
    int levix = 10;
    int leviy = 300;
    int desnix = 1160;
    int desniy = 300;
    Vector2 mousePoint;
    Rectangle prase;
    Rectangle levi;
    Rectangle desni;
    bool reset = false;
    int points1 = 0;
    int points2 = 0;
    int chckst = 1;
    const int brz = 5;

    brzx = 2;
    brzy = 2;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        timer += GetFrameTime();
        if (timer > 0.016f)
        {
            timer = 0;
            frame += 1;
        }

        if (!pravacx)
        {
            x += brzx + brz + vely;
        }
        if (!pravacy)
        {
            y += brzy + brz + vely;
        }

        /* if (x >= screenWidth-50 || x == 10) {
            pravacx = 1;
            // std::cout << "Out of bounds " << std::endl;
        } */

        if (pravacx)
        {
            x -= brzx + brz + velx;
            // std::cout << "u petlji  " << std::endl;
        }
        if (y >= screenHeight - 50 || y == 15)
        {
            pravacy = true;
            // std::cout << "u petlji  " << std::endl;
            // std::cout << "Out of bounds " << std::endl;
        }

        if (pravacy)
        {
            y -= brzy + brz + vely;
            // y -= brzy+vely+velocity+10;
            // std::cout << "pravacx je: " << pravacx << std::endl;
            if (y < 20)
            {
                pravacy = false;
            }
        }

        // Hitboxes
        prase = {(float)x, (float)y, 25, 25};
        desni = {(float)desnix, (float)desniy, 10, 160};
        levi = {(float)levix, (float)leviy, 10, 160};

        // Input handling

        if (IsKeyReleased(KEY_SPACE))
        {
            reset = true;
            chckst = 1;
        }
        if (reset)
        {
            x = 600 - 70;
            y = 300;
            brzx = 2;
            brzy = 2;
            reset = false;
            pravacx = !pravacx;
            pravacy = !pravacy;
        }

        if (IsKeyReleased(KEY_R))
        {
            points1 = 0;
            points2 = 0;
        }

        if (IsKeyDown(KEY_W))
        {
            // Player 1 move up
            if (leviy >= 30)
            {
                leviy -= 20;
            }
        }
        if (IsKeyDown(KEY_S))
        {
            // Player 1 move down
            if (leviy <= 620)
            {
                leviy += 20;
            }
        }
        if (IsKeyDown(KEY_UP))
        {
            // Player 2 move up
            if (desniy >= 30)
            {
                desniy -= 20;
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            // Player 2 move up
            if (desniy <= 620)
            {
                desniy += 20;
            }
        }

        // Collision handling

        if (CheckCollisionRecs(desni, prase))
        {
            pravacx = true;
            // pravacy = !pravacy;
            velx = GetRandomValue(5, 10);
            vely = GetRandomValue(5, 10);
            frame = 0;
        }
        if (CheckCollisionRecs(levi, prase))
        {
            pravacx = false;
            // pravacy = !pravacy;
            velx = GetRandomValue(5, 10);
            vely = GetRandomValue(5, 10);
            frame = 0;
        }

        if (x > 1250 && chckst == 1)
        {
            points1 += 1;
            chckst = 0;
        }

        if (x < -50 && chckst == 1)
        {
            points2 += 1;
            chckst = 0;
        }

        if (frame > 15)
        {
            velx /= 1.2;
            vely /= 1.2;
            frame = 0;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(screenWidth / 2 - 20, 0, 5, 800, WHITE);

        DrawRectangle(x, y, 25, 25, WHITE);
        DrawRectangle(desnix, desniy, 30, 150, WHITE);
        DrawRectangle(levix, leviy, 30, 150, WHITE);
        DrawText("Player 1", 20, 30, 30, DARKBLUE);
        DrawText("R- Reset points", 250, 30, 30, DARKBLUE);
        DrawText("SPACE - serve!", 700, 30, 30, DARKBLUE);
        DrawText(TextFormat("%i", points1), 20, 70, 40, DARKBLUE);
        DrawText("Player 2", 1050, 30, 30, DARKBLUE);
        DrawText("W - Up \nS - Down", 300, 700, 30, DARKBLUE);
        DrawText("Arrow Up - Up \nArrow Down - Down", 700, 700, 30, DARKBLUE);
        DrawText(TextFormat("%i", points2), 1050, 70, 40, DARKBLUE);

        /* DrawRectangle(0, 0, 100, 100, DARKGREEN);
        DrawRectangle(1100, 700, 100, 100, DARKGREEN);
        DrawRectangle(1100, 0, 100, 100, DARKGREEN);
        DrawRectangle(0, 700, 100, 100, DARKGREEN); */

        // DrawTexture(Tex1, screenWidth/2-150, screenHeight/2-150, WHITE);
        // DrawTexture(Tex2, screenWidth/2-400, screenHeight/2-400, WHITE);

        // DrawRectangle(500, 300, 150, 150, WHITE);
        // DrawTexture(Texture2D texture, int posX, int posY, Color tint);

        // DrawText("Congrats! You created your first window!", 0, 0, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}