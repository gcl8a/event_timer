#ifndef __EVENT_TIMER_H
#define __EVENT_TIMER_H

enum TIMER_STATE : uint8_t {TIMER_IDLE, TIMER_RUNNING};

class EventTimer
{
  protected:
    TIMER_STATE timerState = TIMER_IDLE;
    uint32_t startTime = 0;
    uint32_t duration = 0;
    
  public:
    EventTimer(void)
    {
    }
    
    bool CheckExpired(void)
    {
        bool retVal = false;
        if(millis() - startTime > duration && timerState == TIMER_RUNNING) //NOT proper event checking, by the way...
        {
            timerState = TIMER_IDLE;
            retVal = true;
        }
        
        return retVal;
    }
    
    unsigned long Start(unsigned long dur)
    {
      startTime = millis();
      duration = dur;
      timerState = TIMER_RUNNING;
      
      return startTime + dur;
    }
    
    unsigned long Restart(unsigned long dur = 0) //need a better name?
    {
      if(dur != 0) duration = dur;
      startTime += duration;
      timerState = TIMER_RUNNING;
      
      return startTime + duration;
    }
    
    void Cancel(void)
    {
      timerState = TIMER_IDLE;
    }
    
    bool IsRunning(void)
    {
        return timerState == TIMER_RUNNING;
    }
};

#endif
