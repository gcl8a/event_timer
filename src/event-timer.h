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
    
    bool CheckExpired(void);
    unsigned long Start(unsigned long dur);
    unsigned long Restart(unsigned long dur = 0);
    void Cancel(void);
    bool IsRunning(void);
};

#endif
