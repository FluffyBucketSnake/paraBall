#pragma once
#include <SDL2/SDL.h>
#include <vector>

class UIControl;
class UIMenu
{
    private:
        int _current = 0;
        std::vector<UIControl*> _children;

        int pressedTime = 0;
        bool repeatFlag = false;
        char direction = 0;

        const int REPEATSTART = 150;
        const int REPEATINTERVAL = 75;

        void MoveCursor();
        void HandleRepeat(int delta);
        void HandleInput();
    public:
        SDL_Point Position = {0,0};

        int GetCount() const;
        void AddChild(UIControl *child);
        void RemoveChild(int index); 
        void ClearChildren();
        void SetFocus(int index);
        int GetFocus() const;
        void Update(int delta);
        void Render(SDL_Renderer *renderer, int delta);
};