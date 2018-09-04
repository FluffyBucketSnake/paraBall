#pragma once
#include <game.h>
#include <screens/screen.h>

class paraBall : public Game
{
    public:
        virtual void Init();
        virtual void Update(int delta);
        virtual void Render(int delta);
        virtual void Load();
        virtual void Unload();
};