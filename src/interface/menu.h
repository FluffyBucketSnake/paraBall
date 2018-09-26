#pragma once
#include <SDL2/SDL.h>
#include <vector>

class UIControl;
class UIMenu
{
    private:
        //Main container.
        std::vector<UIControl*> _children;
        int _current = 0;
        //Input and control releated stuff.
        int pressedTime = 0;
        bool repeatFlag = false;
        char direction = 0;
        bool _isLocked = false;

        const int REPEATSTART = 150;
        const int REPEATINTERVAL = 75;

        void MoveCursor();
        void HandleRepeat(int delta);
        void HandleInput();
        //Layout related stuff.
        void HandleLayout();
    public:
        SDL_Point Position = {0,0};
        SDL_Rect Size = {128,128};

        int GetCount() const;
        void AddChild(UIControl *child);
        UIControl *GetChild(int index);
        void RemoveChild(int index); 
        void ClearChildren();

        void SetFocus(int index);
        int GetFocus() const;
        void Lock();
        void Unlock();

        void Update(int delta);
        void Render(SDL_Renderer *renderer, int delta);
};