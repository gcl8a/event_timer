#ifndef __EVENT_TIMER_H
#define __EVENT_TIMER_H

class EventTimer
{
  protected:
    uint8_t timerState = 0;
    uint32_t startTime = 0;
    uint32_t duration = 0;
    
  public:
    EventTimer(void)
    {
    }
    
    bool CheckExpired(void)
    {
        bool retVal = false;
        if(millis() - startTime > duration && timerState == 1)
        {
            timerState = 0;
            retVal = true;
        }
        
        return retVal;
    }
    
    unsigned long Start(unsigned long dur)
    {
      startTime = millis();
      duration = dur;
      timerState = 1;
      
      return startTime + dur;
    }
    
    unsigned long Restart(unsigned long dur = 0) //need a better name?
    {
      if(dur != 0) duration = dur;
      startTime += duration;
      timerState = 1;
      
      return startTime + duration;
    }
    
    void Cancel(void)
    {
      timerState = 0;
    }
    
    int IsRunning(void)
    {
        return timerState;
    }
};

#endif
