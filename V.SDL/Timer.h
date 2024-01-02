#ifndef TIMER_H
#define TIMER_H

typedef struct Timer Timer;
typedef void(*TimerCallback)(void *data);

/*
  Initializes the timer mechanism, and allocates resources for 'nTimers'
  number of simultaneous timers.

  Returns non-zero on failure.
*/
int timer_InitTimers(int nTimers);

/*
  Add this to the main game loop, either before or after the loop that
  polls events. If timing is very critical, add it both before and after.
*/
void timer_PollTimers(void);

/*
  Creates an idle timer that has to be started with a call to 'timer_Start()'.

  Returns NULL on failure. Will fail if 'timer_InitTimers()' has not already
  been called.
*/
Timer *timer_Create(Uint32 interval, TimerCallback fCallback, void *data);

/*
  Pauses a timer. If the timer is already paused, this is a no-op.

  Fails with non-zero if 'timer' is NULL or not a valid timer.
*/
int timer_Pause(Timer *timer);

/*
  Starts a timer. If the timer is already running, this function resets the
  delta time for the timer back to zero.

  Fails with non-zero if 'timer' is NULL or not a valid timer.
*/
int timer_Start(Timer *timer);

/*
  Cancels an existing timer. If 'timer' is NULL, this is a no-op.
*/
void timer_Cancel(Timer *timer);

/*
  Releases the resources allocated for the timer mechanism. Call at program
  shutdown, along with 'SDL_Quit()'.
*/
void timer_Quit(void);

/*
  Returns true if the timer is running, or false if the timer is paused or
  is NULL.
*/
int timer_IsRunning(Timer *timer);

#endif