#include "controlbase.h"
#include <iostream>
#include "keyboard.h"

const SDL_Point &ControlBase::GetPosition() const
{
    return _position;
}

void ControlBase::SetPosition(const SDL_Point &value)
{
    _position = value;
}

const SDL_Point &ControlBase::GetSize() const
{
    return _size;
}

void ControlBase::SetSize(const SDL_Point &value)
{
    _size = value;
}

const Margin &ControlBase::GetPadding() const
{
    return _padding;
}

void ControlBase::SetPadding(const Margin &value)
{
    _padding = value;
}

bool ControlBase::GetFocus() const
{
    return _focus;
}

void ControlBase::SetFocus(bool value)
{
    _focus = value;
}

void ControlBase::Click(void *sender)
{
    std::cout << "Clicked!" << std::endl;
}

void ControlBase::Render(int delta, SDL_Renderer *renderer)
{
    //Create bounds.
    SDL_Rect bounds;
    bounds.x = GetPosition().x;
    bounds.y = GetPosition().y;
    bounds.w = GetSize().x;
    bounds.h = GetSize().y;
    //Render.
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderFillRect(renderer,&bounds);
}

std::vector<Control*> &ContainerBase::Controls()
{
    return _controls;
}

void ContainerBase::UpdateLayout()
{
    int accY = 0;
    for(Control *control : _controls)
    {
        //Get values.
        SDL_Point size = control->GetSize();
        Margin padding = control->GetPadding();
        //Calculate width.
        //TODO
        //Set Position.
        control->SetPosition({padding.Left,accY+padding.Top});
        //Increment accumulator.
        accY = padding.Top + size.y + padding.Bottom;
    }
}

void ContainerBase::Update(int delta)
{
    //Check input.
    if (Keyboard::Released(SDL_SCANCODE_RETURN))
    {
        for(Control *control : _controls)
            control->Click(nullptr);
    }
}

void ContainerBase::Render(int delta, SDL_Renderer *renderer)
{
    //Render each control.
    for(Control *control : _controls)
        control->Render(delta,renderer);
}