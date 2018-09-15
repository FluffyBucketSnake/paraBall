#include <interface/listbutton.h>
#include <global.h>
#include <keyboard.h>
#include <exception>
#include <iterator>

void UIListButton::AddItem(std::string item)
{
    _items.push_back(item);  
}

std::string &UIListButton::GetItem(int index)
{
    //Check if index is in-bounds
    if (index < 0 || index >= GetCount())
        throw std::out_of_range("index");
    //Return the reference to the string.
    return _items[index];
}

void UIListButton::RemoveItem(int index)
{
    //Check if index is in-bounds
    if (index < 0 || index >= GetCount())
        throw std::out_of_range("index");
    //Check if the removed item is before the current item.
    if (index <= _current && index != 0)
        SetCurrentIndex(_current-1);
    //Remove the item from the list.
    _items.erase(_items.begin() + index);      
}

void UIListButton::AddItems(std::string items[], int count)
{
    _items.insert(_items.end(),items,items+count);
}

void UIListButton::ClearItems()
{
    //Clear the vector list.
    _items.clear();
    //Set current index to 0.
    _current = 0;
}

int UIListButton::GetCount() const
{
    return _items.size();
}

int UIListButton::GetCurrentIndex() const
{
    return _current;
}

std::string &UIListButton::GetCurrent()
{
    //Check if container isn't empty.
    if (GetCount() < 0)
        throw std::exception();
    else
        return _items[_current];
}

void UIListButton::SetCurrentIndex(int index)
{
    //Check if index is in-bounds
    if (index < 0 || index >= GetCount())
        throw std::out_of_range("index");
    //Update the index.
    _current = index;
}

void UIListButton::MoveCursor()
{
    //Play sound.
    Mix_PlayChannel(-1,SFX_CURSORMOVE,0);
    //Wrap the new index in case of overflow.
    int newIndex = (_current+direction)%GetCount();
    if (newIndex < 0)
        newIndex += GetCount();
    //Set focus.
    SetCurrentIndex(newIndex);
}

void UIListButton::HandleInput()
{
    //Check if user pressed a directional key.
    if (direction == 0)
    {
        if (Keyboard_Pressed(SDL_SCANCODE_A))
            direction = -1;
        else
        if (Keyboard_Pressed(SDL_SCANCODE_D))
            direction = 1;
    }
    //Check if the user released a directional key.
    if (Keyboard_Released(SDL_SCANCODE_A) && direction == -1)
    {
        if (!repeatFlag)
            MoveCursor();
        direction = 0;
    }
    if (Keyboard_Released(SDL_SCANCODE_D) && direction == 1)
    {
        if (!repeatFlag)
            MoveCursor();
        direction = 0;
    }
}

void UIListButton::HandleRepeat(int delta)
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

void UIListButton::OnClick()
{
    //Call parent's method.
    UIButton::OnClick();
    //Lock/Unlock the containing menu.
    if (Parent != NULL)
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

void UIListButton::Update(int delta)
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

void UIListButton::Render(SDL_Renderer *renderer, int delta)
{
    //Update the text.
    if (_isLocked)
        Text = Label + ": < " + GetCurrent() + " >";
    else
        Text = Label + ": " + GetCurrent();
    //Render the control.
    UIButton::Render(renderer,delta);
}