#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TimeDisplay
{
  public:
    TimeDisplay();
    ~TimeDisplay();
    SDL_Renderer *GetRenderer();
    SDL_Window *GetWindow();
    void RenderString(std::string string);
    void Update(int seconds);

  private:
    int Init();
    void Cleanup();
    std::string SecondsToString(int totalSeconds);
    void ClearScreen();
    void Render();

    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth, windowHeight;
    const char *WINDOW_TITLE = "TimeDisplay";

    TTF_Font *font;
    const int fontSize = 400;
    SDL_Color white = {0xFF, 0xFF, 0xFF, 0};
    SDL_Texture *getTTFTextureFromInt(int number);
    SDL_Rect currentTimeRect;
};