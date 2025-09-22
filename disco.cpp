#include <iostream>
#include <cmath>

namespace ray {
    #include <raylib.h>
}

bool playing = false;
int currentSong = 0;  
int back_adv = 0;    

int main() {
    ray::InitWindow(294*2, 211*2, "Cyan Chemistry - Frank Steps");

    ray::Image icon = ray::LoadImage("image/icon/icon.png");
    ray::SetWindowIcon(icon);

    ray::Texture texCyan    = ray::LoadTexture("image/discos/cyan.png");
    ray::Texture texPurple  = ray::LoadTexture("image/discos/purple.png");
    ray::Texture texPink    = ray::LoadTexture("image/discos/pink.png");
    ray::Texture texGreen   = ray::LoadTexture("image/discos/green.png");
    ray::Texture texCooper  = ray::LoadTexture("image/discos/cooper.png");
    ray::Texture texNothing = ray::LoadTexture("image/discos/nothing.png");

    ray::Texture button_cbk = ray::LoadTexture("image/buttons/come_back_button.png");
    ray::Texture button_pse = ray::LoadTexture("image/buttons/pause_button.png");
    ray::Texture button_ply = ray::LoadTexture("image/buttons/play_button.png");
    ray::Texture button_adv = ray::LoadTexture("image/buttons/to_advenced.png");

    ray::InitAudioDevice();
    ray::Sound neod   = ray::LoadSound("sounds/neod.wav");
    ray::Sound mush   = ray::LoadSound("sounds/mush.wav");
    ray::Sound world  = ray::LoadSound("sounds/world.wav");
    ray::Sound cooper = ray::LoadSound("sounds/cooper.wav");
    ray::Sound sweet  = ray::LoadSound("sounds/sweet.wav");

    while (!ray::WindowShouldClose()) {
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

        if (ray::IsKeyPressed(ray::KEY_RIGHT)) {
            if (back_adv < 5) back_adv++;
        }
        if (ray::IsKeyPressed(ray::KEY_LEFT)) {
            if (back_adv > 1) back_adv--;
        }

        if (back_adv != currentSong) {
            ray::StopSound(neod);
            ray::StopSound(mush);
            ray::StopSound(world);
            ray::StopSound(cooper);
            ray::StopSound(sweet);

            currentSong = back_adv;
            playing = true;
        }

        float time = ray::GetTime();
        unsigned char r = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3));
        unsigned char g = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 2));
        unsigned char b = (unsigned char)(127 + 127 * sin(2 * M_PI * time * 0.3 + 4));

        ray::BeginDrawing();
        ray::ClearBackground(ray::BLACK);

        ray::Texture *currentTex = &texNothing;
        const char *songText = "By Frank Steps";

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

        ray::Vector2 pos = {0, 0};
        ray::DrawTextureEx(*currentTex, pos, 0.0f, 2.0f, ray::WHITE);

        ray::DrawText(songText, 10, 280, 38, ray::Color{r, g, b, 255});
        ray::EndDrawing();
    }

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

    ray::UnloadSound(neod);
    ray::UnloadSound(mush);
    ray::UnloadSound(world);
    ray::UnloadSound(cooper);
    ray::UnloadSound(sweet);

    ray::CloseAudioDevice();
    ray::CloseWindow();
    return 0;
}
