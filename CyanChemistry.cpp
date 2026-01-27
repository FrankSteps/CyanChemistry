/*
 Portuguese [PT-BR]

 Tocador de músicas - compostas por: Francisco Passos / Frank Steps
 Desenvolvedor do projeto:           Francisco Passos / Frank Steps
 Desenvolvido em:                    02/08/2025
 Modificado em:                      23/09/2025

 Este programa tem como finalidade usar as funcionalidades de audio e imagem do raylib, bem como
 sua capacidade em reconhecer as teclas que estão sendo pressionadas no teclado.

Este programa é um player de música com a estética inspirada em jogos de RPG antigos. No projeto, o
usuário usa as setas (direita e esquerda) ou os botões de avançar e de retroceder para escolher as músicas. 
A tecla de espaço tem a mesma função do botão de play e pause da música.  

 Informações legais das músicas usadas neste projeto:
 O EP "Cyan Chemistry" e a single "Sweet Childhood" têm Direitos Autorais - CC (Creative Commons):
 Todas as músicas deste projeto foram compartilhadas no YouTube, bandcamp, Spotify e entre outras plataformas, 
 mas com algumas exceções:

 https://www.youtube.com/@Frank_Steps                              (todas as músicas)
 https://franksteps.bandcamp.com/                                  (todas as músicas)
 https://open.spotify.com/intl-pt/artist/6Ow1TOWQonC9AVL3WxHy3d    (exceto sweet Childhood e Bright Cooper)
 https://music.amazon.com.au/artists/B0D2Z8C41S/frank-steps        (exceto sweet Childhood e Bright Cooper)
 https://music.indiefy.net/artist/frank-steps                      (exceto sweet Childhood e Bright Cooper)

 demais plataformas possuem as músicas do EP "Cyan Chemistry" exceto Bright Cooper.

 Observações e detalhes do projeto:
 Planejo acrescentar um arquivo para baixar este projeto em qualquer computador linux usando bash em sua
 arquitetura. O usuário executa o arquivo de download e ele irá baixar todas as bibliotecas, o compilador e
 qualquer outra necessidade para o programa. Após todo o processo, o programa vai poder ser usado normalmente.

 */

// libraries
#include <iostream>
#include <cmath>

// raylib with namespace "ray"
namespace ray {
    #include <raylib.h>
}

// global variables
float scale = 2.0f;
bool playing = false; // vou usar no botão de pause/play
int currentSong = 0;  
int back_adv = 0;    

// main loop
int main() {
    // create window
    ray::InitWindow(294*scale, 220*scale, "Cyan Chemistry - Frank Steps");

    // load icon
    ray::Image icon = ray::LoadImage("image/icon/icon.png");
    ray::SetWindowIcon(icon);

    // load discs textures
    ray::Texture texCyan    = ray::LoadTexture("image/discos/cyan.png");
    ray::Texture texPurple  = ray::LoadTexture("image/discos/purple.png");
    ray::Texture texPink    = ray::LoadTexture("image/discos/pink.png");
    ray::Texture texGreen   = ray::LoadTexture("image/discos/green.png");
    ray::Texture texCooper  = ray::LoadTexture("image/discos/cooper.png");
    ray::Texture texNothing = ray::LoadTexture("image/discos/nothing.png");

    // load buttons textures
    ray::Texture button_cbk = ray::LoadTexture("image/buttons/come_back_button.png");
    ray::Texture button_pse = ray::LoadTexture("image/buttons/pause_button.png");
    ray::Texture button_ply = ray::LoadTexture("image/buttons/play_button.png");
    ray::Texture button_adv = ray::LoadTexture("image/buttons/to_advenced_button.png");

    // load sounds
    ray::InitAudioDevice();
    ray::Sound neod   = ray::LoadSound("sounds/neod.wav");
    ray::Sound mush   = ray::LoadSound("sounds/mush.wav");
    ray::Sound world  = ray::LoadSound("sounds/world.wav");
    ray::Sound cooper = ray::LoadSound("sounds/cooper.wav");
    ray::Sound sweet  = ray::LoadSound("sounds/sweet.wav");

    // window main loop
    while (!ray::WindowShouldClose()) {
        // rainbow effect
        float time = ray::GetTime();
        unsigned char r = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3));
        unsigned char g = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 2));
        unsigned char b = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 4));

        // mouse coordinates
        ray::Vector2 mousePoint = ray::GetMousePosition();

        // positions
        ray::Vector2 pos_dis = {0, 15};
        ray::Vector2 pos_cbk = {124, 367};
        ray::Vector2 pos_ply = {272, 365};
        ray::Vector2 pos_adv = {420, 367};


        // click detections variables
        bool clicked_cbk = false;
        bool clicked_adv = false;
        bool clicked_ply_pse = false;


        // button colisions area 
        ray::Rectangle rect_cbk = {
            pos_cbk.x,
            pos_cbk.y,
            (float)button_cbk.width*scale,
            (float)button_cbk.height*scale
        };

        ray::Rectangle rect_adv = { 
            pos_adv.x, 
            pos_adv.y, 
            (float)button_adv.width*scale, 
            (float)button_adv.height*scale 
        };

        ray::Rectangle rect_ply_pse = {
            pos_ply.x,
            pos_ply.y,
            (float)button_ply.width*scale,
            (float)button_ply.height*scale
        };


        // button click detection
        if (ray::CheckCollisionPointRec(mousePoint, rect_adv) && ray::IsMouseButtonPressed(ray::MOUSE_BUTTON_LEFT)) {
            clicked_adv = true;
        }

        if (ray::CheckCollisionPointRec(mousePoint, rect_cbk) && ray::IsMouseButtonPressed(ray::MOUSE_BUTTON_LEFT)) {
            clicked_cbk = true;
        }

        if (ray::CheckCollisionPointRec(mousePoint, rect_ply_pse) && ray::IsMouseButtonPressed(ray::MOUSE_BUTTON_LEFT)) {
            clicked_ply_pse = true;
            playing = !playing;
            clicked_ply_pse = !clicked_ply_pse;
            if (!playing) {
                ray::PauseSound(neod);
                ray::PauseSound(mush);
                ray::PauseSound(world);
                ray::PauseSound(cooper);
                ray::PauseSound(sweet);
            }          
        }


        // space = play/pause
        if (ray::IsKeyPressed(ray::KEY_SPACE)) {
            playing = !playing;
            clicked_ply_pse = !clicked_ply_pse;
            if (!playing) {
                ray::PauseSound(neod);
                ray::PauseSound(mush);
                ray::PauseSound(world);
                ray::PauseSound(cooper);
                ray::PauseSound(sweet);
            }
        }

        // next song
        if (ray::IsKeyPressed(ray::KEY_RIGHT) || clicked_adv == true) {
            if (back_adv < 5) {
                back_adv++;
            }
            clicked_adv = false;
        }

        // previous song
        if (ray::IsKeyPressed(ray::KEY_LEFT) || clicked_cbk == true) {
            if (back_adv > 0){
                back_adv--;
            }
            clicked_cbk = false;
        }


        // change song
        if (back_adv != currentSong) {
            ray::StopSound(neod);
            ray::StopSound(mush);
            ray::StopSound(world);
            ray::StopSound(cooper);
            ray::StopSound(sweet);

            currentSong = back_adv;
            clicked_ply_pse = true;
            playing = true;
        }

        // default screen (nothing song)
        ray::Texture *currentTex = &texNothing;
        const char *songText = "By Frank Steps";


        // song selection
        if (playing) {
            switch (currentSong) {
                case 1: currentTex = &texCyan;   
                    songText = "Neodymium - Frank Steps"; 
                    if (!ray::IsSoundPlaying(neod)){
                        ray::PlaySound(neod);
                    }  
                break;

                case 2: currentTex = &texPurple;   
                    songText = "Mushrooms - Frank Steps"; 
                    if (!ray::IsSoundPlaying(mush)){
                        ray::PlaySound(mush);
                    }  
                break;

                case 3: currentTex = &texPink;   
                    songText = "Neo World - Frank Steps"; 
                    if (!ray::IsSoundPlaying(world)){
                        ray::PlaySound(world);
                    }  
                break;

                case 4: currentTex = &texCooper;   
                    songText = "Bright Cooper - Frank Steps"; 
                    if (!ray::IsSoundPlaying(cooper)){
                        ray::PlaySound(cooper);
                    }  
                break;

                case 5: currentTex = &texGreen;   
                    songText = "Sweet Childhood - Frank Steps"; 
                    if (!ray::IsSoundPlaying(sweet)){
                        ray::PlaySound(sweet);
                    }  
                break;   
            }
        }


        // draw
        ray::BeginDrawing();
        ray::ClearBackground(ray::BLACK);

        ray::DrawTextureEx(*currentTex, pos_dis, 0.0f, scale, ray::WHITE);
        ray::DrawTextureEx(button_cbk, pos_cbk, 0.0f, scale, ray::WHITE);
        ray::DrawTextureEx(button_adv, pos_adv, 0.0f, scale, ray::WHITE);

        if (playing) {
            ray::DrawTextureEx(button_pse, pos_ply, 0.0f, scale, ray::WHITE);
        } else {
            ray::DrawTextureEx(button_ply, pos_ply, 0.0f, scale, ray::WHITE);
        }

        ray::DrawText(songText, 11, 295, 35, ray::Color{r, g, b, 255});
        ray::EndDrawing();
    }

    // unload textures
    ray::UnloadTexture(texCyan);
    ray::UnloadTexture(texPurple);
    ray::UnloadTexture(texPink);
    ray::UnloadTexture(texGreen);
    ray::UnloadTexture(texCooper);
    ray::UnloadTexture(texNothing);
    ray::UnloadTexture(button_adv);
    ray::UnloadTexture(button_cbk);
    ray::UnloadTexture(button_ply);
    ray::UnloadTexture(button_pse);

    // unload sounds
    ray::UnloadSound(neod);
    ray::UnloadSound(mush);
    ray::UnloadSound(world);
    ray::UnloadSound(cooper);
    ray::UnloadSound(sweet);

    // close everything
    ray::CloseAudioDevice();
    ray::CloseWindow();
    return EXIT_SUCCESS;
}
