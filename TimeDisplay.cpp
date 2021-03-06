#include "TimeDisplay.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Utility.h"

TimeDisplay::TimeDisplay()
{
    windowWidth = 1920;
    windowHeight = 1080;
    Init();
    ClearScreen();
    Render();
}

int TimeDisplay::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    if (TTF_Init() < 0)
    {
        fprintf(stderr, "Couldn't initialize TTF: %s\n", SDL_GetError());
        Cleanup();
        return (2);
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    font = TTF_OpenFont("font.ttf", fontSize);
    if (font == NULL)
    {
        fprintf(stderr, "Couldn't load font: %s\n",
                SDL_GetError());
    }
    return 0;
}

TimeDisplay::~TimeDisplay()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void TimeDisplay::Cleanup()
{
    SDL_Quit();
    TTF_Quit();
}

void TimeDisplay::RenderString(std::string string)
{
}

void TimeDisplay::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderClear(renderer);
}
void TimeDisplay::Render()
{
    SDL_RenderPresent(renderer);
}
void TimeDisplay::Update(int seconds)
{
    ClearScreen();

    SDL_Texture *tex = getTTFTextureFromInt(seconds);
    SDL_RenderCopy(renderer, tex, NULL, &currentTimeRect);
    Render();
    SDL_DestroyTexture(tex);
}

SDL_Renderer *TimeDisplay::GetRenderer()
{
    return renderer;
}

SDL_Window *TimeDisplay::GetWindow()
{
    return window;
}

/*TODO: skapa en struct eller class med Texture, width, height, x, y. Typ "RenderElement" eller så. */

SDL_Texture *TimeDisplay::getTTFTextureFromInt(int number)
{
    std::string message = SecondsToString(number);
    SDL_Surface *text;

    text = TTF_RenderUTF8_Solid(font, message.c_str(), fgColor); //Draw string to surface
    if (text == NULL)
    {
        fprintf(stderr, "Couldn't render text: %s\n", SDL_GetError());
        TTF_CloseFont(font);
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, text);
    currentTimeRect.x = 0;
    currentTimeRect.y = 0;
    currentTimeRect.w = text->w;
    currentTimeRect.h = text->h;

    SDL_FreeSurface(text);
    return tex;
}

std::string TimeDisplay::SecondsToString(int totalSeconds)
{
    std::string retString;
    bool lessThanZero = false;
    if (totalSeconds < 0)
    {
        lessThanZero = true;
        totalSeconds = totalSeconds * -1;
    }
    int hours = totalSeconds / (60 * 60);
    int minutes = (totalSeconds - hours * 60 * 60) / 60;
    int seconds = totalSeconds - (hours * 60 * 60) - (minutes * 60);

    retString = Utility::PadToTwo(std::to_string(hours)) +
                ":" + Utility::PadToTwo(std::to_string(minutes)) +
                ":" + Utility::PadToTwo(std::to_string(seconds));
    if (lessThanZero)
        retString = std::string(overtimePrefix) + retString;
    return retString;
}