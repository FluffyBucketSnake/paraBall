#include <screens/screenmanager.h>

int ScreenManager::AddScreen(Screen *screen, int priority, int depth, bool enabled, bool visible)
{
    //Checar se a tela eh valida.
    if (screen == NULL)
        return -1;
    //Verificar se ha colisao de ordem.
    bool changed = true;
    while(changed)
    {
        changed = false;
        for(auto it = _metadata.begin(); it != _metadata.end() && !changed; it++)
        {
            if (it->Priority == priority)
            {
                priority++;
                changed = true;
            }
            if (it->Depth == depth)
            {
                depth++;
                changed = true;
            }
        }
    }
    //Adicionar a tela nas listas.
    int id = _screens.size();
    _screens.push_back(screen);
    _metadata.push_back({priority,depth});
    if (enabled)
        _enabled.insert({id,priority});
    if (visible)
        _visible.insert({id,depth});
    //Retornar chave.
    return id;
}

void ScreenManager::RemoveScreen(int id)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Remover a tela das listas.
    _enabled.erase({id,_metadata[id].Priority});
    _visible.erase({id,_metadata[id].Depth});
    _metadata.erase(_metadata.begin()+id);
    _screens.erase(_screens.begin()+id);
}

bool ScreenManager::ContainsID(int id)
{
    //Checar se o ID esta dentro de [0,no de elementos em _screen].
    return (id >= 0 && id < _screens.size());
}

bool ScreenManager::ContainsScreen(Screen* screen)
{
    for(auto it = _screens.begin(); it != _screens.end(); it++)
        if(*it == screen)
            return true;
    return false;
}

void ScreenManager::ClearScreens()
{
    //Liberar todas as telas da memoria.
    for(auto it = _screens.begin(); it != _screens.end(); it++)
        delete *it;
    //Limpar todas as listas.
    _screens.clear();
    _metadata.clear();
    _enabled.clear();
    _visible.clear();
}

Screen *ScreenManager::GetScreen(int id)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return NULL;
    //Retornar ponteiro.
    return _screens[id];
}

void ScreenManager::SetScreen(int id, Screen *screen)
{

    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Modificar tela.
    _screens[id] = screen;
}

void ScreenManager::ToggleUpdate(int id, bool state)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Verificar se a tela esta no loop de execucao. Se estiver, marcar para modificacao, se nao, mudar.
    if (updateLoop)
        _toggles.push({id,state});
    else
    {
        //Verificar se a tela deve ser adicionada ou removida.
        if (state)
            _enabled.insert({id,_metadata[id].Priority});
        else
            _enabled.erase({id,_metadata[id].Priority});
    }
}

void ScreenManager::ToggleRender(int id, bool state)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Verificar se a tela esta no loop de execucao. Se estiver, marcar para modificacao, se nao, mudar.
    if (renderLoop)
        _toggles.push({id,state});
    else
    {
        //Verificar se a tela deve ser adicionada ou removida.
        if (state)
            _visible.insert({id,_metadata[id].Depth});
        else
            _visible.erase({id,_metadata[id].Depth});
    }
}

void ScreenManager::GetStates(int id, bool *enabled, bool *visible)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Verificar os estados.
    if (enabled != NULL)
        *enabled = _enabled.find({id,_metadata[id].Priority}) != _enabled.end();
    if (visible != NULL)
        *visible = _visible.find({id,_metadata[id].Depth}) != _visible.end();
}

int ScreenManager::GetPriority(int id)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return 0;
    else
        return _metadata[id].Priority;
}

void ScreenManager::SetPriority(int id, int priority)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Verificar se ha colisao de ordem.
    bool changed = true;
    while(changed)
    {
        changed = false;
        for(auto it = _metadata.begin(); it != _metadata.end() && !changed; it++)
        {
            if (it->Priority == priority)
            {
                priority++;
                changed = true;
            }
        }
    }
    //Reordenar a tela.
    ToggleUpdate(id,false);
    //Modificar os metadados.
    _metadata[id].Priority = priority; 
    ToggleUpdate(id,true);
}

int ScreenManager::GetDepth(int id)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return 0;
    else
        return _metadata[id].Depth;
}

void ScreenManager::SetDepth(int id, int depth)
{
    //Checar se a tela eh valida.
    if (id >= _screens.size() || id < 0)
        return;
    //Verificar se ha colisao de ordem.
    bool changed = true;
    while(changed)
    {
        changed = false;
        for(auto it = _metadata.begin(); it != _metadata.end() && !changed; it++)
        {
            if (it->Depth == depth)
            {
                depth++;
                changed = true;
            }
        }
    }
    ToggleRender(id,false);
    //Modificar os metadados.
    _metadata[id].Depth = depth; 
    ToggleRender(id,true);
}

void ScreenManager::Update(int delta)
{
    //Definir bandeira de controle.
    updateLoop = true;
    //Executar cada tela.
    for(auto it = _enabled.begin(); it != _enabled.end(); it++)
        _screens[it->ScreenIndex]->Update(delta);
    //Redefinir bandeira.
    updateLoop = false;
    //Aplicar mudancas marcadas.
    while(!_toggles.empty())
    {
        Toggle toggle = _toggles.front();
        ToggleUpdate(toggle.Screen,toggle.State);
        _toggles.pop();
    }
}

void ScreenManager::Render(SDL_Renderer *renderer,int delta)
{
    //Definir bandeira de controle.
    renderLoop = true;
    for(auto it = _visible.begin(); it != _visible.end(); it++)
        _screens[it->ScreenIndex]->Render(renderer,delta);
    //Redefinir bandeira.
    renderLoop = false;
    //Aplicar mudancas marcadas.
    while(!_toggles.empty())
    {
        Toggle toggle = _toggles.front();
        ToggleRender(toggle.Screen,toggle.State);
        _toggles.pop();
    }
}