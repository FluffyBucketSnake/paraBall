#pragma once
#include <game.h>
#include <screens/screen.h>
#include "interface/controlbase.h"

class paraBall : public Game
{
    private:
        ContainerBase container;
    public:
        paraBall() : container(){}

        void Init();
        void Update(int delta);
        void Render(int delta);
        void Load();
        void Unload();
};