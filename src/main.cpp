#include <iostream>
#include <data.h>
#include <paraBall.h>
#include <global.h>
#include <cstring>

bool IsNumber(const char* cstring)
{
    int current = 0;
    while(cstring[current] != '\0')
    {
        if (!isdigit(cstring[current]))
            return 0;
        current++;
    }
    return 1;
}

void PrintHelp()
{
    //TITLE v. VERSION
    //*Subtitle*
    //Commands:
    //*Commands*
    std::cout << TITLE << " v. " << VERSION << std::endl;
    std::cout << "A pong-like game." << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  --help  Prints this prompt." << std::endl;
    std::cout << "  -w --width [WIDTH]          Changes the window/resolution width." << std::endl;
    std::cout << "  -h --height [HEIGHT]        Changes the window/resolution height." << std::endl;
    std::cout << "  -f --fullscreen [0|1|2]     Toggle fullscreen. 0 for windowed, 1 for fullscreen and 2 for window fullscreen." << std::endl;
    std::cout << "  -mf --maxfps [MAXFPS]       Set the FPS cap." << std::endl;
    std::cout << "  -mv --mastervolume [VOLUME] Changes the master volume." << std::endl;
}

void PrintError(const char* arg)
{
    std::cerr << "'" << arg << "' isn't a valid argument or is badly construct.";
    PrintHelp();
}

int LoadArguments(int argc, char* args[])
{
    //Iterate over every item in the argument list, except the first(Application command).
    for (int i = 1; i < argc; i++)
    {
        std::cout << args[i] << std::endl;
        if (strcmp("--help",args[i]) == 0)   //--help
        {
            PrintHelp();
            return 0;
        }
        else if (strcmp("--width",args[i]) == 0 || strcmp("-w",args[i]) == 0) //-w --width
        {
            //Check if argument is valid.
            if ((i+1) == argc || !IsNumber(args[i+1]))
            {
                PrintError(args[i]);
                return 0;
            }
            //Set the window's width.
            CONFIGTRACKER.SetResolution({std::stoi(args[i+1]),CONFIGTRACKER.GetResolution().y});
            //Jump the param's argument.
            i++;
        }
        else if (strcmp("--height",args[i]) == 0 || strcmp("-h",args[i]) == 0) //-h --height
        {
            //Check if argument is valid.
            if ((i+1) == argc || !IsNumber(args[i+1]))
            {
                PrintError(args[i]);
                return 0;
            }
            //Set the window's height.
            CONFIGTRACKER.SetResolution({CONFIGTRACKER.GetResolution().x,std::stoi(args[i+1])});
            //Jump the param's argument.
            i++;
        }
        else if (strcmp("--fullscreen",args[i]) == 0 || strcmp("-f",args[i]) == 0) //-f --fullscreen
        {
            //Check if argument is valid.
            if ((i+1) == argc || !IsNumber(args[i+1]))
            {
                PrintError(args[i]);
                return 0;
            }
            //Change the window mode.
            switch(std::stoi(args[i+1]))
            {
                case 0: CONFIGTRACKER.SetWindowFlags(0); break;
                case 1: CONFIGTRACKER.SetWindowFlags(SDL_WINDOW_FULLSCREEN); break;
                case 2: CONFIGTRACKER.SetWindowFlags(SDL_WINDOW_FULLSCREEN_DESKTOP); break;
            }
            //Jump the param's argument.
            i++;
        }
        else if (strcmp("--fpsmax",args[i]) == 0 || strcmp("-mf",args[i]) == 0) //-mf --fpsmax
        {
            //Check if argument is valid.
            if ((i+1) == argc || !IsNumber(args[i+1]))
            {
                PrintError(args[i]);
                return 0;
            }
            //Set the window's width.
            CONFIGTRACKER.SetMaxFPS(std::stoi(args[i+1]));
            //Jump the param's argument.
            i++;
        }
        else if (strcmp("--mastervolume",args[i]) == 0 || strcmp("-mv",args[i]) == 0) //-mv --mastervolume
        {
            std::cout << "Volume toggle." << std::endl;
            //Check if argument is valid.
            if ((i+1) == argc || !IsNumber(args[i+1]))
            {
                PrintError(args[i]);
                return 0;
            }
            //Set the window's width.
            CONFIGTRACKER.SetMasterVolume(std::stoi(args[i+1])*128/100.0);
            //Jump the param's argument.
            i++;
        }
        else
        {
            PrintError(args[i]);
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* args[])
{
    //paraBall --weight 360 --height 240 --fps 60
    paraBall game;
    GAME = &game;
    //Open config.
    DATAFILE.Open(SDL_GetBasePath() + std::string("data"));
    DATAFILE.Load();
    //Create ConfigTracker.
    CONFIGTRACKER.Init((Game*)&game);
    //Load config.
    CONFIGTRACKER.LoadConfig(DATAFILE);
    //Load setting arguments. If it returns 1, the application must run. If it return 0, the application must not run(Parse Error/Help).
    if (LoadArguments(argc,args))
        return game.Run();
}