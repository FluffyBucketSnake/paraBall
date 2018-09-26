#include <screens/optionsscreen.h>
#include <interface/listbutton.h>
#include <interface/slider.h>
#include <global.h>
#include <graphics/colors.h>

int OptionsScreen::curWndMode;
int OptionsScreen::curResolution;
int OptionsScreen::curMaxFPS;
int OptionsScreen::curMstVol;

void OptionsScreen::Apply()
{
    //Window flags
    if (CONFIGTRACKER.GetWindowFlags() != WINDOWMODES[curWndMode])
        CONFIGTRACKER.SetWindowFlags(WINDOWMODES[curWndMode]);
    //Resolution.
    SDL_Point current = CONFIGTRACKER.GetResolution();
    SDL_Point desired = RESOLUTIONS[curResolution];
    if (current.x != desired.x || current.y != desired.y)
        CONFIGTRACKER.SetResolution(desired);
    //Max fps
    if (CONFIGTRACKER.GetMaxFPS() != MAXFPS[curMaxFPS])
        CONFIGTRACKER.SetMaxFPS(MAXFPS[curMaxFPS]);
    //Master volume.
    if (CONFIGTRACKER.GetMasterVolume() != curMstVol*255/100)
        CONFIGTRACKER.SetMasterVolume(curMstVol);
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
    //Master Volume button.
    UISlider *mstVlmBtn = new UISlider;
    mstVlmBtn->Label = "Master Volume";
    mstVlmBtn->SetRange(Range<int>(0,100));
    mstVlmBtn->FontStyle = FONT_NORMAL;
    mstVlmBtn->Margin = 2;
    menu.AddChild(mstVlmBtn);
    //Apply button.
    UIButton *applyBtn = new UIButton;
    applyBtn->Text = "Apply";
    applyBtn->Margin = 2;
    applyBtn->FontStyle = FONT_NORMAL;
    applyBtn->ClickEvent = &Apply;
    menu.AddChild(applyBtn);
    //Go Back button.
    UIButton *goBackBtn = new UIButton;
    goBackBtn->Text = "Go Back";
    goBackBtn->Margin = 2;
    goBackBtn->FontStyle = FONT_NORMAL;
    goBackBtn->ClickEvent = &GoBack;
    menu.AddChild(goBackBtn);
}

void OptionsScreen::Resume()
{
    //Load config.
    //Window mode.
    switch(CONFIGTRACKER.GetWindowFlags())
    {
        case SDL_WINDOW_FULLSCREEN_DESKTOP:
            curResolution = 1; break;
        case SDL_WINDOW_FULLSCREEN:
            curResolution = 2; break;
        default: curResolution = 0; break;
    }
    //Resolution.
    SDL_Point currentRes = CONFIGTRACKER.GetResolution();
    if (currentRes.x == 640 && currentRes.y == 480)
        curResolution = 1;
    else if (currentRes.x == 1280 && currentRes.y == 960)
        curResolution = 2;
    else
        curResolution = 0;
    //Max fps.
    switch(CONFIGTRACKER.GetMaxFPS())
    {
        case 30: curMaxFPS = 1; break;
        case 60: curMaxFPS = 2; break;
        default: curMaxFPS = 0; break;
    }
    //Master volume.
    curMstVol = CONFIGTRACKER.GetMasterVolume()*100/255;
    //Reset focus.
    menu.SetFocus(0);
}

void OptionsScreen::Unload()
{
    menu.ClearChildren();
}

void OptionsScreen::Update(int delta)
{
    //Update values.
    curWndMode = ((UIListButton*)menu.GetChild(0))->GetCurrentIndex();
    curResolution = ((UIListButton*)menu.GetChild(1))->GetCurrentIndex();
    curMaxFPS = ((UIListButton*)menu.GetChild(2))->GetCurrentIndex();
    curMstVol = ((UISlider*)menu.GetChild(3))->GetValue();
    //Update menu.
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