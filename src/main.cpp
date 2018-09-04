#include <paraBall.h>

int main(int argc, char* args[])
{
    //paraBall --weight 360 --height 240 --fps 60
    paraBall game;
    game.FPS = 60;
    //Rodar jogo.
    return game.Run();
}