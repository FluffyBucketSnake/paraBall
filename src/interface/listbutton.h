#pragma once
#include <interface/button.h>

class UIListButton : public UIButton
{
    private:
        std::vector<std::string> _items;
        int _current = 0;

        int pressedTime = 0;
        bool repeatFlag = false;
        char direction = 0;
        bool _isLocked = false;

        const int REPEATSTART = 150;
        const int REPEATINTERVAL = 75;

        void MoveCursor();
        void HandleRepeat(int delta);
        void HandleInput();
    protected:
        virtual void OnClick();
    public:
        std::string Label = "";

        void AddItem(std::string item);
        std::string &GetItem(int index);
        void RemoveItem(int index);
        void AddItems(std::string items[], int count);
        void ClearItems();
        int GetCount() const;

        int GetCurrentIndex() const;
        std::string &GetCurrent();
        void SetCurrentIndex(int index);

        void Update(int delta);
        void Render(SDL_Renderer *renderer, int delta);
};