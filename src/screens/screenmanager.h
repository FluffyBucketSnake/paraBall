#pragma once
#include <set>
#include <queue>
#include <vector>
#include <SDL2/SDL.h>
#include <screens/screen.h>

class ScreenManager
    {
    public:
        int AddScreen(Screen *screen, int priority, int depth, bool enabled=true, bool visible=true);
        void RemoveScreen(int id);
        bool ContainsID(int id);
        bool ContainsScreen(Screen* screen);
        void ClearScreens();

        Screen *GetScreen(int id);
        void SetScreen(int id, Screen *screen);

        void ToggleUpdate(int id, bool state);
        void ToggleRender(int id, bool state);
        void GetStates(int id, bool *enabled, bool *visible);

        int GetPriority(int id);
        void SetPriority(int id, int priority);
        int GetDepth(int id);
        void SetDepth(int id, int depth);

        void Update(int delta);
        void Render(SDL_Renderer* renderer, int delta);
    private:
        struct Metadata{
            int Priority, Depth;
        };
        struct Item{
            int ScreenIndex, Priority;
            bool operator<(const Item &a) const
            {
                return this->Priority < a.Priority;
            }
            bool operator>(const Item &a) const
            {
                return this->Priority > a.Priority;
            }
        };
        struct Toggle{
            int Screen;
            bool State;
        };
        std::vector<Screen*> _screens;
        std::vector<Metadata> _metadata;
        std::set<Item,std::less<Item>> _enabled;
        std::set<Item,std::greater<Item>> _visible;
        bool updateLoop = false;
        bool renderLoop = false;
        std::queue<Toggle> _toggles;
};