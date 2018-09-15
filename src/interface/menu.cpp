#include <interface/menu.h>
#include <interface/control.h>
#include <keyboard.h>
#include <global.h>
#include <exception>

void UIMenu::AddChild(UIControl *control)
{
    //Add child.
    control->Parent = this;
    _children.push_back(control);
    //If first, focus it.
    if (GetCount()-1 == 0)
        SetFocus(0);
}

void UIMenu::RemoveChild(int index)
{
    //Check if index is valid.
    if (index < 0 || index >= GetCount())
        throw std::out_of_range("index");
    //Check if the focus index is after the removed item.
    if (index <= _current && index != 0)
        SetFocus(_current-1);
    //Free memory.
    delete _children[index];
    //Remove child from list.
    _children.erase(_children.begin() + index);
}

void UIMenu::ClearChildren()
{
    //Remove, starting with the first, every control in the menu.
    while (GetCount() != 0)
        RemoveChild(0);
}

int UIMenu::GetCount() const
{
    return _children.size();
}

int UIMenu::GetFocus() const
{
    return _current;
}

void UIMenu::Lock()
{
    //Lock the menu.
    _isLocked = true;
    //Reset input controls.
    pressedTime = 0;
    repeatFlag = 0;
    direction = 0;
}

void UIMenu::Unlock()
{
    _isLocked = false;
}

void UIMenu::SetFocus(int index)
{
    //Check if the menu is locked. If it is, ignore.
    if (_isLocked)
        return;
    //Check if index is valid.
    if (index < 0 || index >= GetCount())
        throw std::out_of_range("index");
    //Update controls.
    _children[_current]->IsFocused = false;
    _children[index]->IsFocused = true;
    _current = index;
}

void UIMenu::MoveCursor()
{
    //Play sound.
    Mix_PlayChannel(-1,SFX_CURSORMOVE,0);
    //Wrap the new index in case of overflow.
    int newIndex = (_current+direction)%GetCount();
    if (newIndex < 0)
        newIndex += GetCount();
    //Set focus.
    SetFocus(newIndex);
}

void UIMenu::HandleInput()
{
    //Check if user pressed a directional key.
    if (direction == 0)
    {
        if (Keyboard_Pressed(SDL_SCANCODE_W))
            direction = -1;
        else
        if (Keyboard_Pressed(SDL_SCANCODE_S))
            direction = 1;
    }
    //Check if the user released a directional key.
    if (Keyboard_Released(SDL_SCANCODE_W) && direction == -1)
    {
        if (!repeatFlag)
            MoveCursor();
        direction = 0;
    }
    if (Keyboard_Released(SDL_SCANCODE_S) && direction == 1)
    {
        if (!repeatFlag)
            MoveCursor();
        direction = 0;
    }
}

void UIMenu::HandleRepeat(int delta)
{
    if (direction != 0)
    {
        pressedTime += delta;
        if (repeatFlag)
        {
            if (pressedTime >= REPEATINTERVAL)
            {
                MoveCursor();
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

void UIMenu::HandleLayout()
{
    //Initialize accumulator variables.
    int curY = 0;
    //Iterate over every control, in order.
    for (int i = 0; i < _children.size(); i++)
    {
        //Define the layout position of the control.
        _children[i]->_layoutPosition.x = Position.x;
        _children[i]->_layoutPosition.y = Position.y + curY;
        //Increase the accumulator value.
        curY += _children[i]->GetSize().y;
    }
}

void UIMenu::Update(int delta)
{
    //Check if the menu isn't locked.
    if (!_isLocked)
    {
        //Handle input.
        HandleInput();
        //Handle repeat.
        HandleRepeat(delta);
    }
    //Update every control.
    for(auto it = _children.begin(); it != _children.end(); it++)
        (*it)->Update(delta);
    //Update the layout.
    HandleLayout();
}

void UIMenu::Render(SDL_Renderer *renderer, int delta)
{
    //Render every control.
    for(auto it = _children.begin(); it != _children.end(); it++)
        (*it)->Render(renderer,delta);
}