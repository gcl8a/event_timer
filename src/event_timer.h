#ifndef __EVENT_TIMER_H
#define __EVENT_TIMER_H

#include <Arduino.h>

class EventTimer
{
  enum TIMER_STATE : uint8_t {TIMER_IDLE, TIMER_RUNNING};

  protected:
    TIMER_STATE timerState = TIMER_IDLE;
    uint32_t startTime = 0;
    uint32_t duration = 0;
    
  public:
    EventTimer(void) {}
    EventTimer(unsigned long dur);
    
    bool CheckExpired(bool restart = false);
    unsigned long Start(unsigned long dur);
    unsigned long start(unsigned long dur) {return Start(dur);}
    
    unsigned long Restart(unsigned long dur = 0);
    unsigned long Snooze(unsigned long dur = 0) {return Restart(dur);}
    void Cancel(void);
    bool IsRunning(void);
};

#endif
