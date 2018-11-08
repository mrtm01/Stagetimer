#include "Timer.h"
#include <iostream>
#include "TimeDisplay.h"

TimeDisplay *Timer::_timeDisplay = NULL;
Timer *Timer::_timer = NULL;

Timer::Timer()
{
    SDL_InitSubSystem(SDL_INIT_TIMER);
    std::cout << "Timer Created!" << std::endl;
    _timer = this;
    paused = true;
    timerID = SDL_AddTimer(standardInterval, TimerCallback, this);
    duration = 0;
    startTime = 0;
}
Timer::~Timer()
{
    SDL_RemoveTimer(timerID);
    _timer = NULL;
}

void Timer::Start()
{
    startTime = SDL_GetTicks() / 1000;
    paused = false;
}

void Timer::SetTime(int duration)
{
    startTime = SDL_GetTicks() / 1000;
    this->duration = duration;
    _timeDisplay->Update(duration);
}

void Timer::Pause()
{
    duration = GetSecondsLeft(); //store this for when we start the timer again.
    std::cout << "Timer paused, duration " << duration << " stored." << std::endl;
    paused = true;
}

void Timer::SetTimeDisplay(TimeDisplay *td)
{
    _timeDisplay = td;
}

Uint32 Timer::TimerCallback(Uint32 interval, void *param)
{
    if (param != NULL)
    {
        Timer *t = static_cast<Timer *>(param);
        return t->Callback2(interval);
    }

    return 200;
}

Uint32 Timer::Callback2(Uint32 interval)
{
    if (!paused)
        _timeDisplay->Update(GetSecondsLeft());
    return standardInterval;
}

int Timer::GetSecondsLeft()
{
    int currentTime = SDL_GetTicks();
    return duration - ((currentTime / 1000) - startTime);
}

bool Timer::IsPaused()
{
    return paused;
}