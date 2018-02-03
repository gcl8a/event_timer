#ifndef __EVENT_TIMER_H
#define __EVENT_TIMER_H

#include <RTClib.h>

class Alarm
{
protected:
    uint32_t alarm; //seconds after midnight
    uint32_t prevTime;
    
    int isRunning;
    int isAlarming;
public:
    Alarm(void)
    {
        isRunning = 0;
        isAlarming = 0;
        prevTime = (uint32_t)-1;
    }
    
    int32_t Set(int32_t hour, int32_t min, int32_t sec)
    {
        alarm = 3600UL * hour + 60UL * min + sec;
        isRunning = 1;
        isAlarming = 0;
        
        return alarm;
    }
    
//    int CheckAlarm(int32_t hour, int32_t min, int32_t sec) //current time
//    {
//        int32_t currTime = 3600L * hour + 60L * min + sec;
//        if(prevTime == -1) prevTime = currTime; //first time through, set to currTime (compiler gives a warning...ignore it)
//        
//        if(!isRunning) return 0;
//        
//        //the trick is dealing with the roll-over at midnight
//        //we'll deal with it using differences:
//        int32_t deltaTime = currTime - prevTime;
//        if(deltaTime < 0) deltaTime += 86400L;
//        
//        int32_t deltaAlarm = currTime - alarm;
//        if(deltaAlarm < 0) deltaAlarm += 86400L;
//        
//        if(deltaAlarm < deltaTime) //passed the alarm time
//        {
//            isAlarming = 1; //note that nowhere in this function do we set isAlarming to 0: alarm goes until Quiet'ed
//        }
//        
//        prevTime = currTime;
//        
//        return isAlarming;
//    }
    
    int CheckAlarm(uint32_t currTime) //current time in absolute seconds since, what is it, 2000?
    {
        //rtc.GetCurrentTime();
        if(prevTime == (uint32_t)(-1) || currTime < prevTime) prevTime = currTime; //first time through or on clock change, set to currTime
        
        if(!isRunning) return 0;
        
        //the trick is dealing with the roll-over at midnight
        int32_t deltaTime = currTime - prevTime;
        if(deltaTime < 0) deltaTime += 86400UL;
        
        int32_t deltaAlarm = (currTime % 86400UL) - alarm;
        if(deltaAlarm < 0) deltaAlarm += 86400UL;
        
        if(deltaAlarm < deltaTime) //passed the alarm time
        {
            isAlarming = 1; //note that nowhere in this function do we set isAlarming to 0: alarm goes until Quiet'ed
        }
        
        prevTime = currTime;
        
        return isAlarming;
    }
    
    //    int Snooze(void)
    //    {
    //        isAlarming = 0;
    //    }
    
    void Quiet(void)
    {
        isAlarming = 0; //but leave it running
    }
    
    void Cancel(void)
    {
        isRunning = 0;
        isAlarming = 0;
    }
};

//class AlarmAbs
//{
//protected:
//    DateTime alarm; // seconds from Jan 1 2000, or whenever it is...
//    //int32_t prevTime;
//    
//    int isRunning;
//    int isAlarming;
//public:
//    AlarmAbs(void)
//    {
//        isRunning = 0;
//        isAlarming = 0;
//        //prevTime = -1;
//    }
//    
//    DateTime Set(const DateTime& dt)
//    {
//        alarm = dt;
//        isRunning = 1;
//        isAlarming = 0;
//        
//        return alarm;
//    }
//    
//    DateTime Set(const DateTime& now, int32_t hour, int32_t min, int32_t sec)
//    {
//        uint32_t prevMidnight = now.secondstime() / SECONDS_PER_DAY;
//        uint32_t alarmSeconds = prevMidnight + (3600UL * hour + 60UL * min + sec);
//        if(alarmSeconds < now.secondstime()) alarmSeconds += SECONDS_PER_DAY;
//        alarm = DateTime(alarmSeconds);
//        
//        isRunning = 1;
//        isAlarming = 0;
//        
//        return alarm;
//    }
//    
//    int CheckAlarm(const DateTime& currDT) //current time
//    {
//        if(!isRunning) {isAlarming = 0;}
//        else if(isAlarming) {} //keep alarming, even if the clock has been set back(?)
//        else if(currDT.secondstime() > alarm.secondstime()) isAlarming = 1;
//        
//        return isAlarming;
//    }
//    
//    DateTime Snooze(uint32_t snoozeDelay)
//    {
//        isAlarming = 0; //but leave it running
//        alarm = alarm + snoozeDelay;
//        
//        return alarm;
//    }
//    
//    void Quiet(void)
//    {
//        isAlarming = 0; //but leave it running
//    }
//    
//    void Cancel(void)
//    {
//        isRunning = 0;
//        isAlarming = 0;
//    }
//};

class Timer
{
  protected:
    int timerState;
    unsigned long startTime;
    unsigned long duration;
    
  public:
    Timer(void)
    {
      timerState = 0;
      startTime = 0;
      duration = 0;
    }
    
    boolean CheckExpired(void)
    {
      if(millis() - startTime > duration && timerState == 1)
      {
        timerState = 0;
        return true;
      }

      else
        return false;
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
      startTime += duration;
      if(dur != 0) duration = dur;
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
