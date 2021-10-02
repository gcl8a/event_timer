#include <event-timer.h>

bool EventTimer::CheckExpired(void)
{
    bool retVal = false;
    if(millis() - startTime > duration && timerState == TIMER_RUNNING)
    {
        timerState = TIMER_IDLE;
        retVal = true;
    }
    
    return retVal;
}

unsigned long EventTimer::Start(unsigned long dur)
{
  startTime = millis();
  duration = dur;
  timerState = TIMER_RUNNING;
  
  return startTime + dur;
}

unsigned long EventTimer::Restart(unsigned long dur) //need a better name?
{
  if(dur != 0) duration = dur;
  startTime += duration;
  timerState = TIMER_RUNNING;
  
  return startTime + duration;
}

void EventTimer::Cancel(void)
{
  timerState = TIMER_IDLE;
}

bool EventTimer::IsRunning(void)
{
    return timerState == TIMER_RUNNING;
}
