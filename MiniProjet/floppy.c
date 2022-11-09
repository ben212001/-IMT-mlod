/*******************************************************************************************
*
*   raylib - classic game: floppy
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//COMPILATION
// gcc floppy.c -Wall -std=c11 /Users/ben/Documents/_IMT_NORD_EUROPE/M1/MLOD/Raylib.git/src/libraylib.a -lm  -Wno-missing-braces -s  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo -DPLATFORM_DESKTOP
// puis ./a.out 
#include "raylib.h"
#include <stdio.h>
#include <time.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define MAX_TUBES 200
#define FLOPPY_RADIUS 24
#define TUBES_WIDTH 80
#define MAX_PORTAILS MAX_TUBES/5                   //je souhaite créer un portail par lot de 5 tuyaux

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Floppy {
    Vector2 position;
    int radius;
    Color color;
} Floppy;

typedef struct Tubes {
    Rectangle rec;
    Color color;
    bool active;
} Tubes;

typedef struct Portails {
    Rectangle rec;
    Color color;
} Portails;                                          //création du struct Portails

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static bool gameOver = false;
static bool pause = false;
static int score = 0;
static int hiScore = 0;

static Floppy floppy = { 0 };
static Tubes tubes[MAX_TUBES*2] = { 0 };
static Vector2 tubesPos[MAX_TUBES] = { 0 };
static int tubesSpeedX = 0;
static bool superfx = false;
static Portails portails[MAX_PORTAILS] = { 0 };      //je crée le tableau qui contiendra tous les portails existants
static Vector2 portailsPos[MAX_PORTAILS] = { 0 };    //je crée le tableau qui contient les coordonées de position de chaque portail

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)
static void UpdateGameBis(int);     // Update the game when a portal has been activated
static void UpdateGameTer(void);    // // Update the game when a second portal has been activated
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: floppy REMASTERED BY BENJAMIN PUZENAT");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    floppy.radius = FLOPPY_RADIUS;
    floppy.position = (Vector2){80, screenHeight/2 - floppy.radius};
    tubesSpeedX = 2;
    int posTuyauAvecPortail = 0;        //cette variable sert à choisir le numéro du tuyau qui sera dôté d'un portail
    int positionTuyauMultipleCinq = 0;       //cette variable vaudra 0 puis 10 puis 20... et sert à 
    int incrementPortail = 0;

    for (int i = 0; i < MAX_TUBES; i++)
    {
        tubesPos[i].x = 400 + 280*i;
        tubesPos[i].y = -GetRandomValue(0, 120);

        if ((i+1)%5 == 0)
        {
            posTuyauAvecPortail = positionTuyauMultipleCinq + GetRandomValue(0, 4);
            portailsPos[incrementPortail].x = tubesPos[posTuyauAvecPortail].x;
            portailsPos[incrementPortail].y = tubesPos[posTuyauAvecPortail].y;
            positionTuyauMultipleCinq += 5;
            incrementPortail += 1;
        }
    }

    incrementPortail = 0;

    for (int i = 0; i < MAX_TUBES*2; i += 2)
    {
        tubes[i].rec.x = tubesPos[i/2].x;
        tubes[i].rec.y = tubesPos[i/2].y;
        tubes[i].rec.width = TUBES_WIDTH;
        tubes[i].rec.height = 255;

        tubes[i+1].rec.x = tubesPos[i/2].x;
        tubes[i+1].rec.y = 600 + tubesPos[i/2].y - 240;
        tubes[i+1].rec.width = TUBES_WIDTH;
        tubes[i+1].rec.height = 255;

        tubes[i/2].active = true;
        if ((i+2)%10 == 0)
        {
            portails[incrementPortail].rec.x = portailsPos[incrementPortail].x + 40;
            portails[incrementPortail].rec.y = portailsPos[incrementPortail].y + 290;
            portails[incrementPortail].rec.width = TUBES_WIDTH/2;
            portails[incrementPortail].rec.height = 255/6;
            incrementPortail += 1;
        }
    }

    score = 0;

    gameOver = false;
    superfx = false;
    pause = false;
}


// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            for (int i = 0; i < MAX_TUBES; i++)
            { 
                tubesPos[i].x -= tubesSpeedX;
            }

            for (int i = 0; i < MAX_TUBES*2; i += 2)
            {
                tubes[i].rec.x = tubesPos[i/2].x;
                tubes[i+1].rec.x = tubesPos[i/2].x;   
            }

            for (int i = 0; i < MAX_PORTAILS; i++)
            { 
                portailsPos[i].x -= tubesSpeedX;
                portails[i].rec.x = portailsPos[i].x;
            }

            if (IsKeyDown(KEY_SPACE) && !gameOver) floppy.position.y -= 4;
            else floppy.position.y += 2;

            // Check Collisions
            for (int i = 0; i < MAX_TUBES*2; i++)
            {
                if (CheckCollisionCircleRec(floppy.position, floppy.radius, tubes[i].rec))
                {
                    gameOver = true;
                    pause = false;
                }
                else if ((tubesPos[i/2].x < floppy.position.x) && tubes[i/2].active && !gameOver)
                {
                    score += 100;
                    tubes[i/2].active = false;

                    superfx = true;

                    if (score > hiScore) hiScore = score;
                }
                
                for (int i = 0; i < MAX_PORTAILS; i++)
                {   
                    int compteurDeI = i;
                    if (CheckCollisionPointRec(floppy.position, portails[i].rec))
                    {   
                        tubesSpeedX *= 3;
                        floppy.radius /= 3;
                        for(int i =1; i <= 60 * 5; i++)
                        {
                            UpdateGameBis(compteurDeI);
                            DrawGame();
                        }
                        tubesSpeedX /= 3;
                        floppy.radius = FLOPPY_RADIUS;
                    }
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Update game when a portal has been activated (one frame)
void UpdateGameBis(int compteurDeI)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            for (int i = 0; i < MAX_TUBES; i++)
            { 
                tubesPos[i].x -= tubesSpeedX;
            }

            for (int i = 0; i < MAX_TUBES*2; i += 2)
            {
                tubes[i].rec.x = tubesPos[i/2].x;
                tubes[i+1].rec.x = tubesPos[i/2].x;   
            }

            for (int i = 0; i < MAX_PORTAILS; i++)
            { 
                portailsPos[i].x -= tubesSpeedX;
                portails[i].rec.x = portailsPos[i].x;
            }

            if (IsKeyDown(KEY_SPACE) && !gameOver) floppy.position.y -= 4;
            else floppy.position.y += 2;

            // Check Collisions
            for (int i = 0; i < MAX_TUBES*2; i++)
            {
                if (CheckCollisionCircleRec(floppy.position, floppy.radius, tubes[i].rec))
                {
                    gameOver = true;
                    pause = false;
                }
                else if ((tubesPos[i/2].x < floppy.position.x) && tubes[i/2].active && !gameOver)
                {
                    score += 100;
                    tubes[i/2].active = false;

                    superfx = true;

                    if (score > hiScore) hiScore = score;
                }
                
                for (int i = compteurDeI + 1; i < MAX_PORTAILS; i++)
                {
                    if (CheckCollisionPointRec(floppy.position, portails[i].rec))
                    {   
                        tubesSpeedX *= 1.5;
                        floppy.radius /= 3;
                        for(int i =1; i <= 60 * 2; i++)
                        {
                            UpdateGameTer();
                            DrawGame();
                        }
                        tubesSpeedX /= 1.5;
                        floppy.radius = FLOPPY_RADIUS/3;
                    }
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Update game when a second portal has been activated (one frame)
void UpdateGameTer(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            for (int i = 0; i < MAX_TUBES; i++)
            { 
                tubesPos[i].x -= tubesSpeedX;
            }

            for (int i = 0; i < MAX_TUBES*2; i += 2)
            {
                tubes[i].rec.x = tubesPos[i/2].x;
                tubes[i+1].rec.x = tubesPos[i/2].x;   
            }

            for (int i = 0; i < MAX_PORTAILS; i++)
            { 
                portailsPos[i].x -= tubesSpeedX;
                portails[i].rec.x = portailsPos[i].x;
            }

            if (IsKeyDown(KEY_SPACE) && !gameOver) floppy.position.y -= 4;
            else floppy.position.y += 2;

            // Check Collisions
            for (int i = 0; i < MAX_TUBES*2; i++)
            {
                if (CheckCollisionCircleRec(floppy.position, floppy.radius, tubes[i].rec))
                {
                    gameOver = true;
                    pause = false;
                }
                else if ((tubesPos[i/2].x < floppy.position.x) && tubes[i/2].active && !gameOver)
                {
                    score += 100;
                    tubes[i/2].active = false;

                    superfx = true;

                    if (score > hiScore) hiScore = score;
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(BLANK);

        if (!gameOver)
        {
            DrawCircle(floppy.position.x, floppy.position.y, floppy.radius, RED);

            // Draw tubes
            for (int i = 0; i < MAX_TUBES; i++)
            {
                DrawRectangle(tubes[i*2].rec.x, tubes[i*2].rec.y, tubes[i*2].rec.width, tubes[i*2].rec.height, PINK);
                DrawRectangle(tubes[i*2 + 1].rec.x, tubes[i*2 + 1].rec.y, tubes[i*2 + 1].rec.width, tubes[i*2 + 1].rec.height, PINK);
            }

            for (int i = 0; i < MAX_PORTAILS; i++)
            {
                DrawRectangle(portails[i].rec.x, portails[i].rec.y, portails[i].rec.width, portails[i].rec.height, BLUE);
            }

            // Draw flashing fx (one frame only)
            if (superfx)
            {
                //DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                superfx = false;
            }

            DrawText(TextFormat("%04i", score), 20, 20, 40, YELLOW);
            DrawText(TextFormat("HI-SCORE: %04i", hiScore), 20, 70, 20, GOLD);

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        else {DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, ORANGE);
            DrawText(TextFormat("FINAL SCORE: %04i", score), 200, 260, 40, YELLOW);
            DrawText(TextFormat("HI-SCORE: %04i", hiScore), 320, 300, 20, GOLD);
        }
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}