#include <interface/slider.h>
#include <keyboard.h>

int UISlider::GetValue() const
{
    return _value;
}

void UISlider::SetValue(int value)
{
    _value = _range.Clamp(value);
}

const Range<int> UISlider::GetRange() const
{
    return _range;
}

void UISlider::SetRange(Range<int> range)
{
    _range = range;
    SetValue(GetValue());
}

void UISlider::MoveCursor()
{
    //Set focus.
    SetValue(_value+speed);
}

void UISlider::HandleRepeat(int delta)
{
    if (speed != 0)
    {
        pressedTime += delta;
        if (repeatFlag)
        {
            if (pressedTime >= REPEATINTERVAL)
            {
                MoveCursor();
                if (speed > 0)
                    speed = std::min(_range.Distance(),speed+1);
                else
                    speed = std::max(-_range.Distance(),speed-1);;
                pressedTime %= REPEATINTERVAL;
            }
        }
        else
        {
            if (pressedTime >= REPEATSTART)
            {
                MoveCursor();
                repeatFlag = true;
                pressedTime %= REPEATSTART;
            }
        }
    }
    else
    {
        pressedTime = 0;
        repeatFlag = false;
    }
}

void UISlider::HandleInput()
{
    //Check if user pressed a directional key.
    if (speed == 0)
    {
        if (Keyboard::Pressed(SDL_SCANCODE_A))
            speed = -1;
        else
        if (Keyboard::Pressed(SDL_SCANCODE_D))
            speed = 1;
    }
    //Check if the user released a directional key.
    if (Keyboard::Released(SDL_SCANCODE_A) && speed < 0)
    {
        if (!repeatFlag)
            MoveCursor();
        speed = 0;
    }
    if (Keyboard::Released(SDL_SCANCODE_D) && speed > 0)
    {
        if (!repeatFlag)
            MoveCursor();
        speed = 0;
    }
}

void UISlider::OnClick()
{
    //Call parent's method.
    UIButton::OnClick();
    //Lock/Unlock the containing menu.
    if (Parent != nullptr)
    {
        if (!_isLocked)
        {
            Parent->Lock();
            _isLocked = true;
        }
        else
        {
            Parent->Unlock();
            _isLocked = false;
        }
    }
}

void UISlider::Update(int delta)
{
    //Check if control is locked.
    if (_isLocked)
    {
        HandleInput();
        HandleRepeat(delta);
    }
    //Call parent's method.
    UIButton::Update(delta);
}

void UISlider::Render(SDL_Renderer *renderer, int delta)
{
    //Update the text.
    if (Label.empty())
    {
        if (_isLocked)
            Text = "< " + std::to_string(GetValue()) + " >";
        else
            Text = std::to_string(GetValue());
    }
    else
    {
        if (_isLocked)
            Text = Label + ": < " + std::to_string(GetValue()) + " >";
        else
            Text = Label + ": " + std::to_string(GetValue());
    }
    //Render the control.
    UIButton::Render(renderer,delta);
}