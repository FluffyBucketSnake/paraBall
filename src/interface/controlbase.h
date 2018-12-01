#include "control.h"

class ControlBase : public Control
{
    private:
        SDL_Point _position = {0,0};
        SDL_Point _size = {0,0};
        Margin _padding = {0,0,0,0};
        bool _focus = false;
    public:
        ControlBase(const SDL_Point &position, const SDL_Point &size)
        {
            _position = position;
            _size = size;
        }
        ControlBase(const SDL_Point &position, const SDL_Point &size, const Margin &padding)
            : ControlBase(position, size)
        {
            _padding = padding;
        }

        const SDL_Point &GetPosition() const;
        void SetPosition(const SDL_Point &value);
        const SDL_Point &GetSize() const;
        void SetSize(const SDL_Point &value);
        const Margin &GetPadding() const;
        void SetPadding(const Margin &value);
        bool GetFocus() const;
        void SetFocus(bool value);

        void Click(void *sender) ;
        void Render(int delta, SDL_Renderer *renderer);
};

class ContainerBase : public Container
{
    private:    
        std::vector<Control*> _controls;
    public:
        std::vector<Control*> &Controls();
        void UpdateLayout();
        void Update(int delta);
        void Render(int delta, SDL_Renderer *renderer);
};