/*
 Portuguese [PT-BR]

 Tocador de músicas - compostas por: Francisco Passos / Frank Steps
 Desenvolvedor do projeto:           Francisco Passos / Frank Steps
 Desenvolvido em:                    02/08/2025
 Modificado em:                      22/09/2025

 Este programa tem como finalidade usar as funcionalidades de audio e imagem da SFML, bem como
 sua capacidade em reconhecer as teclas que estão sendo pressionadas no teclado.

 Este programa consiste em tocar (ou pausar) as músicas. Funcionando como um tocador.
 Assim que uma tecla númerica (do 1 ao 5) é pressionada, a música toca e imagem muda.
 Ao clicar em "espaço", qualquer música que esteja tocando é pausada mudando assim para uma outra
 imagem.
 Brevemente pretendo trocar a funcionalidade dos botões do teclado para botões interativos na telas

 Informações legais das músicas:
 O EP "CyanChemistry" e a single "Sweet Childhood" têm Direitos Autorais - CC (Creative Commons):
 Todas as músicas deste projeto foram compartilhadas no YouTube, bandcamp e Spotify, mas com algumas
 exceções:

 https://www.youtube.com/@Frank_Steps                              (todas as músicas)
 https://franksteps.bandcamp.com/                                  (todas as músicas)
 https://open.spotify.com/intl-pt/artist/6Ow1TOWQonC9AVL3WxHy3d    (exceto sweet Childhood e Bright Cooper)
 https://music.amazon.com.au/artists/B0D2Z8C41S/frank-steps        (exceto sweet Childhood e Bright Cooper)
 https://music.indiefy.net/artist/frank-steps                      (exceto sweet Childhood e Bright Cooper)

 Quem sabe eu não lance mais alguma ainda este ano (2025)... Mas é improvável...

 Observações e detalhes do projeto:
 Planejo acrescentar um arquivo para baixar este projeto em qualquer computador linux usando bash em sua
 arquitetura. O usuário executa o arquivo de download e ele irá baixar todas as bibliotecas, o compilador e
 qualquer outra necessidade para o programa. Após todo o processo, o programa vai poder ser usado normalmente.


 English [EN-USA]:
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
bool playing = false;
int currentSong = 0;  
int back_adv = 0;    

// main loop
int main() {
    // create window
    ray::InitWindow(294*scale, 211*scale, "Cyan Chemistry - Frank Steps");

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
        ray::Vector2 mousePoint = ray::GetMousePosition();

        // positions
        ray::Vector2 pos = {0, 0};
        ray::Vector2 pos_cbk = {124, 352};
        ray::Vector2 pos_pse = {272, 350};
        ray::Vector2 pos_ply = {272, 350};
        ray::Vector2 pos_adv = {420, 352};

        // click detections variables
        bool clicked_cbk = false;
        bool clicked_pse = false;
        bool clicked_ply = false;
        bool clicked_adv = false;


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

        // button click detection
        if (ray::CheckCollisionPointRec(mousePoint, rect_adv) && ray::IsMouseButtonPressed(ray::MOUSE_LEFT_BUTTON)) {
            clicked_adv = true;
        }

        if (ray::CheckCollisionPointRec(mousePoint, rect_cbk) && ray::IsMouseButtonPressed(ray::MOUSE_LEFT_BUTTON)) {
            clicked_cbk = true;
        }

        // space = play/pause
        if (ray::IsKeyPressed(ray::KEY_SPACE)) {
            playing = !playing;
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
            playing = true;
        }

        // rainbow effect
        float time = ray::GetTime();
        unsigned char r = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3));
        unsigned char g = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 2));
        unsigned char b = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 4));

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

        ray::DrawTextureEx(*currentTex, pos, 0.0f, scale, ray::WHITE);

        ray::DrawTextureEx(button_ply, pos_ply, 0.0f, scale, ray::WHITE);
        ray::DrawTextureEx(button_cbk, pos_cbk, 0.0f, scale, ray::WHITE);
        ray::DrawTextureEx(button_adv, pos_adv, 0.0f, scale, ray::WHITE);

        ray::DrawText(songText, 10, 280, 38, ray::Color{r, g, b, 255});
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
