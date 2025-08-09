/*
 Portuguese [PT-BR]

 Tocador de músicas - compostas por: Francisco Passos / Frank Steps
 Desenvolvedor do projeto:           Francisco Passos / Frank Steps
 Desenvolvido em:                    02/08/2025
 Modificado em:                      06/08/2025 - 5:05 AM (hehe - Artic. M.)

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


 English [EN-USA]
 Traduza por conta própria, que tal? Ou não sabe usar um  tradutor?!
 Tem o duolingo caso queira um caminho mais difícil. Aprende português logo, é legal. Precisei dela para
 passar no meu vestibular e ingressar na faculdade de CC (significa "Cheiro Corporal").
 */

//bibliotecas utilizadas no projeto
#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>

//declarando os namespaces
using namespace std;
using namespace sf;    

//variáveis para o uso dos botões
bool playing = false; 
int back_adv = 0;
int currentSong = 0;

int main() {
    RenderWindow window(VideoMode(294, 211), "Disco - Frank Steps"); 
    Clock rainbowClock; 

    //bloco de códigos responsáveis pelos textos que estão no projeto
    Font pixel;
    pixel.loadFromFile("fonts/pixel_art.ttf");

    Text songName;
    songName.setFont(pixel);
    songName.setCharacterSize(14);
    songName.setFillColor(Color::White);
    songName.setPosition(5, 140);
    songName.setString("By Frank Steps");

    //bloco de códigos responsáveis pelas imagens do projeto
    Image 
        icon, play, pause, advenced, back
    ;

    //ícone do projeto
    icon.loadFromFile ("image/icon/icon.png");
    window.setIcon (icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Texture 
        texCyan, texPurple, texPink, texGreen, texCooper, texNothing, 
        texPlay, texBack, texPause, texAdvenced
    ;
    
    //gerenciamento das demais imagens que estão no projeto
    texCyan.loadFromFile ("image/discos/cyan.png");
    texPurple.loadFromFile ("image/discos/purple.png");
    texPink.loadFromFile ("image/discos/pink.png");
    texGreen.loadFromFile ("image/discos/green.png");
    texCooper.loadFromFile ("image/discos/cooper.png");
    texNothing.loadFromFile ("image/discos/nothing.png");
    texPlay.loadFromFile ("image/buttons/play_button.png");
    texBack.loadFromFile ("image/buttons/come_back_button.png");
    texPause.loadFromFile ("image/buttons/pause_button.png");
    texAdvenced.loadFromFile ("image/buttons/to_advenced_button.png");

    Sprite 
        sCyan (texCyan), sPurple (texPurple), sPink (texPink), sGreen (texGreen), 
        sCooper (texCooper), sNothing (texNothing), sPlay(texPlay), sBack(texBack), 
        sPause(texPause), sAdvenced(texAdvenced)
    ;

    //ponteiros dos sprites
    Sprite* currentSprite = nullptr;
    Sprite* currentPlayButton = &sPlay;

    //posicionando os elementos/imagens na tela antes de mostrá-las
    sBack.setPosition(62, 176);
    sPlay.setPosition(136, 175);
    sPause.setPosition(136, 175);
    sAdvenced.setPosition(210, 176);

    //Bloco responsável pelos sons do projeto
    SoundBuffer 
        bufferNeod, bufferMush, bufferWorld, bufferSweet, bufferCooper
    ;

    bufferNeod.loadFromFile ("sounds/neod.wav");
    bufferMush.loadFromFile ("sounds/mush.wav");
    bufferWorld.loadFromFile ("sounds/world.wav");
    bufferSweet.loadFromFile ("sounds/sweet.wav");
    bufferCooper.loadFromFile ("sounds/cooper.wav");

    Sound 
        Neod, Mush, World, Sweet, Cooper
    ;

    Neod.setBuffer (bufferNeod);
    Mush.setBuffer (bufferMush);
    World.setBuffer (bufferWorld);
    Sweet.setBuffer (bufferSweet);
    Cooper.setBuffer (bufferCooper);

    //Loop principal - Aqui é onde todo o software é gerenciado
    Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed){
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                if(sAdvenced.getGlobalBounds().contains(mousePos)){
                    if(back_adv < 5){
                        back_adv++;
                    } else {
                        playing = true;
                    }
                }
                if(sBack.getGlobalBounds().contains(mousePos)){
                    if(back_adv > 1){
                        back_adv--;
                    } else {
                        playing = true;
                    }
                }
                if(sPlay.getGlobalBounds().contains(mousePos) || sPause.getGlobalBounds().contains(mousePos)){
                    playing = !playing;
                    if(playing == true){
                        currentPlayButton = &sPause;
                    } else {
                        currentPlayButton = &sPlay;             
                    }
                }
                if (playing) {
                    switch (currentSong) {
                        case 1: Neod.play(); break;
                        case 2: Mush.play(); break;
                        case 3: World.play(); break;
                        case 4: Cooper.play(); break;
                        case 5: Sweet.play(); break;
                    }
                }
            }
            if (back_adv != currentSong){
                Neod.stop();
                Mush.stop();
                World.stop();
                Cooper.stop();
                Sweet.stop();

                if(back_adv == 1){
                    cout << "Tocando Neodymium - Frank Steps\n";
                    songName.setString("Neodymium - Frank Steps");
                    currentSprite = &sCyan;
                    Neod.play();
                } else if (back_adv == 2) {
                    cout << "Tocando Mushrooms - Frank Steps\n";
                    songName.setString("Mushrooms - Frank Steps");
                    currentSprite = &sPurple;
                    Mush.play();
                } else if (back_adv == 3) {
                    cout << "Tocando Neo World - Frank Steps\n";
                    songName.setString("Neo World - Frank Steps");
                    currentSprite = &sPink;
                    World.play();
                } else if (back_adv == 4) {
                    cout << "Tocando Bright Cooper - Frank Steps\n";
                    songName.setString("Bright Cooper - Frank Steps");
                    currentSprite = &sCooper;
                    Cooper.play();
                } else if (back_adv == 5) {
                    cout << "Tocando Sweet Childhood - Frank Steps\n";
                    songName.setString("Sweet Childhood - Frank Steps");
                    currentSprite = &sGreen;
                    Sweet.play();
                }
                currentSong = back_adv;
            }
            else if (!playing){
                Neod.pause();
                Mush.pause();
                World.pause();
                Cooper.pause();
                Sweet.pause();
            }
        }
        // Exibição da imagem atual
        window.clear(Color::Black);
        if (currentSprite) {
            window.draw(*currentSprite);
        } else {
            window.draw(sNothing);
        }
        //efeito arco-iris por intermédio das funções trigonométricas - estudar mais sobre a biblioteca cmath
        float time = rainbowClock.getElapsedTime().asSeconds();
        Uint8 r = static_cast<Uint8>(127 + 127 * sin(2 * 3.141590 * time * 0.3));
        Uint8 g = static_cast<Uint8>(127 + 127 * sin(2 * 3.141590 * time * 0.3 + 2));
        Uint8 b = static_cast<Uint8>(127 + 127 * sin(2 * 3.141590 * time * 0.3 + 4));
        songName.setFillColor(Color(r, g, b));

        //por fim, mostrando os elementos na tela
        window.draw(songName);
        window.draw(*currentPlayButton);
        window.draw(sBack);
        window.draw(sAdvenced);
        window.display();
    }
    return 0;
}
