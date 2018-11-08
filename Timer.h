#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include <SDL2/SDL_timer.h>
#include "TimeDisplay.h"

class Timer
{
  public:
    Timer();
    ~Timer();
    void Start();
    void SetTime(int duration);
    void Pause();
    void SetTimeDisplay(TimeDisplay *td);
    bool IsPaused();

  private:
    static Uint32 TimerCallback(Uint32 interval, void *param);
    int GetSecondsLeft();
    bool paused;
    int duration;
    SDL_TimerID timerID;
    static TimeDisplay *_timeDisplay;
    static Timer *_timer;
    Uint32 Callback2(Uint32 interval);
    const int standardInterval = 200;
    int startTime;
};
