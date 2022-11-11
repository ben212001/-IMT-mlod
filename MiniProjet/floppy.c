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
    int positionTuyauMultipleCinq = 0;       //cette variable vaudra 0 puis 5 puis 10... et sert à initailiser posTuyauAvecPortail
    int incrementPortail = 0;               //cette variable va permettre de parcourir toutes les éléments du tableau portailPos

    for (int i = 0; i < MAX_TUBES; i++)
    {
        tubesPos[i].x = 400 + 280*i;
        tubesPos[i].y = -GetRandomValue(0, 120);

        if ((i+1)%5 == 0)   //je parcours ce if tous les 5 passages dans le for, après que 5 nouveaux tuyaux ont été initialisés
        {
            posTuyauAvecPortail = positionTuyauMultipleCinq + GetRandomValue(0, 4);  // tirage au sort d'un des 5 nouveaux tuyaux créés qui sera alors dôté d'un portail 
            portailsPos[incrementPortail].x = tubesPos[posTuyauAvecPortail].x;       // le portail prend les mêmes coordonées en abscisses que le tuyau qu'il complète
            portailsPos[incrementPortail].y = tubesPos[posTuyauAvecPortail].y;       // le portail prend les mêmes coordonées en ordonnées que le tuyau qu'il complète
            positionTuyauMultipleCinq += 5;         // cette variable est actualisée pour être prête à l'emploi lors du prochain passage dans le if
            incrementPortail += 1;                  // idem
        }
    }

    incrementPortail = 0;  //on réinitialise cette variable pour pouvoir ensuite de nouveau parcourir les éléments du tableau portails

    for (int i = 0; i < MAX_TUBES*2; i += 2)
    {
        tubes[i].rec.x = tubesPos[i/2].x;
        tubes[i].rec.y = tubesPos[i/2].y;
        tubes[i].rec.width = TUBES_WIDTH;
        tubes[i].rec.height = 255;

        tubes[i+1].rec.x = tubesPos[i/2].x;
        tubes[i+1].rec.y = 600 + tubesPos[i/2].y - 200;
        tubes[i+1].rec.width = TUBES_WIDTH;
        tubes[i+1].rec.height = 255;

        tubes[i/2].active = true;
        if ((i+2)%10 == 0)         // on passe dans le if tous les 5 passages dans le for, après que 5 couples de tuyaux supérieur-inférieur ont été positionnés
        {
            portails[incrementPortail].rec.x = portailsPos[incrementPortail].x;   //  on positionne le portail à la même abscisse que le tuyau
            portails[incrementPortail].rec.y = portailsPos[incrementPortail].y + 290;   // on positionne le portail entre le tuyau supérieur et le tuyau inférieur
            portails[incrementPortail].rec.width = TUBES_WIDTH/2;     // le portail fait la moitié de la largeur du tuyau
            portails[incrementPortail].rec.height = 255/6;    // le portail fait 1/6 de la hauteur du tuyau
            incrementPortail += 1;     // on incrémente pour pouvoir accéder au portail suivant lors du prochain passage dans le if
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

            for (int i = 0; i < MAX_PORTAILS; i++) //pour chaque frame, on déplace TOUS les portails... 
            { 
                portailsPos[i].x -= tubesSpeedX;  // ...à la même vitesse de défilement que les tuyaux
                portails[i].rec.x = portailsPos[i].x; // on actualise donc la position du portail
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
                
                for (int i = 0; i < MAX_PORTAILS; i++)      // //pour chaque frame, on vérifie pour TOUS les portails... 
                {   
                    int compteurDeI = i;  // sera utile pour l'appel de la fonction UpdateGameBis
                    if (CheckCollisionPointRec(floppy.position, portails[i].rec))  // ...si le CENTRE de floppy n'a pas percuté un de ces portails (ses bordures peuvent toucher les portails sans les activer)
                    {   //en cas de percussion de floppy avec un portail:
                        tubesSpeedX *= 3;   // on mutiplie par 3 la vitesse de défilemet du jeu
                        floppy.radius /= 3;     //on réduit d'un facteur 3 la taille de floppy
                        for(int i =1; i <= 60 * 5; i++)  //en considérant que chaque seconde compte 60 frames, on maintient les 2 changements précédents pendant 5sec.
                        {
                            UpdateGameBis(compteurDeI);  //on continue à faire tourner le jeu via UpdateGameBis mais sans considérer le tuyau qui a été actionné, ni ceux d'avant d'ailleurs (sinon la fonction UpdateGame s'appelle à chaque frame, répétant les 2 changements précédents à chaque frame et entraînant une injouabilité (vitesse augmente beaucoup trop vite))
                            DrawGame(); // on actualise l'affichage du jeu 
                        }
                        tubesSpeedX /= 3;  // on retourne aux paramètres initiaux
                        floppy.radius = FLOPPY_RADIUS;  // on retourne aux paramètres initiaux
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
                
                for (int i = compteurDeI + 1; i < MAX_PORTAILS; i++)    //pour chaque frame, on vérifie pour TOUS les portails... 
                {
                    if (CheckCollisionPointRec(floppy.position, portails[i].rec))  // ...si le centre de floppy n'a pas percuté un de ces portails (ses bordures peuvent toucher les portails sans les activer)
                    {   
                        tubesSpeedX *= 1.5;  // on mutiplie par 1,5 la vitesse de défilemet du jeu
                        floppy.radius /= 3;     //on réduit d'un facteur 3 la taille de floppy
                        for(int i =1; i <= 60 * 2; i++)     //en considérant que chaque seconde compte 60 frames, on maintient les 2 changements précédents pour 2sec.
                        {
                            UpdateGameTer();        //on continue à faire tourner le jeu via UpdateGameTer
                            DrawGame();         // on actualise l'affichage du jeu 
                        }
                        tubesSpeedX /= 1.5;     // on retourne aux paramètres initiaux
                        floppy.radius = FLOPPY_RADIUS/3;        // on retourne aux paramètres initiaux
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

// Update game when a second portal has been activated (one frame). La particularité est que dorénavant la collision avec un 3ème portail, alors que les effets des 2 premiers sont toujours actifs, n'active aucun effet (la vitesse de jeu serait trop rapide sinon)
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
            }  // ici on n'ajoute pas la boucle qui contrôle les collisions entre floppy et les portails car on ne souhaite pas que les portails aient des effets
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

            for (int i = 0; i < MAX_PORTAILS; i++) //on dessine les portails, de manière analogue au dessin des tuyaux (cf juste au dessus)
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
            DrawText(TextFormat("FINAL SCORE: %04i", score), 200, 260, 40, YELLOW);  //le score final s'affiche quand même une fois la partie terminée
            DrawText(TextFormat("HI-SCORE: %04i", hiScore), 320, 300, 20, GOLD);    //le high-score s'affiche quand même une fois la partie terminée
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