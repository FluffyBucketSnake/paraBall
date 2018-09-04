#pragma once
#include <screens/screen.h>
#include <entities/player.h>
#include <entities/ball.h>

class LevelScreen : public Screen
{
    private:
        Player player;  //Classe do jogador.
        Ball ball;  //Classe da bola.
        
        void HandlePSCollision();    //Cuida da colisao do jogador-tela.
        void HandleBSCollision();    //Cuida da colisao do bola-tela.
        void HandleBPCollision();    //Cuida da colisao do bola-jogador.
    public:
        int Points;

        LevelScreen();
        
        void Point();   //Cuida da vitoria.
        void Lose();    //Cuida da derrota.
        void Reset();
        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
};