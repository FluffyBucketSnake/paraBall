#pragma once
#include <interface/button.h>
#include <range.h>

class UISlider : public UIButton
{
    private:
        int _value = 0;
        Range<int> _range = Range<int>(0,100);

        int pressedTime = 0;
        bool repeatFlag = false;
        char speed = 0;
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
        
        int GetValue() const;
        void SetValue(int value);
        const Range<int> GetRange() const;
        void SetRange(Range<int> range);

        void Update(int delta);
        void Render(SDL_Renderer *renderer, int delta);
};