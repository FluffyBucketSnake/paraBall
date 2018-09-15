#include <screens/optionsscreen.h>
#include <interface/listbutton.h>
#include <global.h>
#include <graphics/colors.h>

void OptionsScreen::Apply()
{

}

void OptionsScreen::GoBack()
{
    //Parar esta tela.
    SCREENMANAGER.ToggleUpdate(OPTIONSSCREEN,false);
    SCREENMANAGER.ToggleRender(OPTIONSSCREEN,false);
    //Rodar titulo.
    SCREENMANAGER.ToggleUpdate(TITLESCREEN,true);
    SCREENMANAGER.ToggleRender(TITLESCREEN,true);
}

void OptionsScreen::Init()
{
    //Menu.
    menu.Position = {96,32};
    //Window mode button.
    UIListButton *windowModeBtn = new UIListButton;
    windowModeBtn->Label = "Window Mode";
    std::string windowModeItems[] = {"Window","Wnd. Fullscr.", "Fullscreen"};
    windowModeBtn->AddItems(windowModeItems,3);
    windowModeBtn->FontStyle = FONT_NORMAL;
    windowModeBtn->Margin = 2;
    menu.AddChild(windowModeBtn);
    //Resolution button.
    UIListButton *resolutionBtn = new UIListButton;
    resolutionBtn->Label = "Resolution";
    std::string resolutionItems[] = {"320x240","640x480", "1280x960"};
    resolutionBtn->AddItems(resolutionItems,3);
    resolutionBtn->FontStyle = FONT_NORMAL;
    resolutionBtn->Margin = 2;
    menu.AddChild(resolutionBtn);
    //Resolution button.
    UIListButton *maxFPSBtn = new UIListButton;
    maxFPSBtn->Label = "Max FPS";
    std::string maxFPSItems[] = {"Uncapped","30", "60"};
    maxFPSBtn->AddItems(maxFPSItems,3);
    maxFPSBtn->FontStyle = FONT_NORMAL;
    maxFPSBtn->Margin = 2;
    menu.AddChild(maxFPSBtn);
    //Apply button.
    UIButton *applyBtn = new UIButton;
    applyBtn->Text = "Apply";
    applyBtn->Margin = 2;
    applyBtn->FontStyle = FONT_NORMAL;
    applyBtn->Event_Pressed = &Apply;
    menu.AddChild(applyBtn);
    //Go Back button.
    UIButton *goBackBtn = new UIButton;
    goBackBtn->Text = "Go Back";
    goBackBtn->Margin = 2;
    goBackBtn->FontStyle = FONT_NORMAL;
    goBackBtn->Event_Pressed = &GoBack;
    menu.AddChild(goBackBtn);
}

void OptionsScreen::Resume()
{
    menu.SetFocus(0);
}

void OptionsScreen::Unload()
{
    menu.ClearChildren();
}

void OptionsScreen::Update(int delta)
{
    menu.Update(delta);
}

void OptionsScreen::Render(SDL_Renderer *renderer, int delta)
{
    //Draw a transparent overlay over the background.
    SDL_SetRenderDrawColor(renderer,0,0,0,235);
    SDL_Rect screenBounds = {0,0,SCREENWIDTH,SCREENHEIGHT};
    SDL_RenderFillRect(renderer,&screenBounds);
    //Options.
    Font::Render(renderer,FONT_TITLE,"OPTIONS",{8,8},COLR_WHITE,FVec2(0.5f),FA_TopLeft,0);
    //Render menu.
    menu.Render(renderer,delta);
}