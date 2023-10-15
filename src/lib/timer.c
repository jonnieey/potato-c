#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "../config.h"
#include "timer.h"
#include "utils.h"

void send_notification_based_on_timertype(TimerType type)
{
  switch (type) {
    case POMODORO_TYPE:
      send_notification(POMODORO_NOTIF_TITLE, POMODORO_NOTIF_BODY);
      break;

    case SHORT_PAUSE_TYPE: 
      send_notification(SHORT_PAUSE_NOTIF_TITLE, SHORT_PAUSE_NOTIF_BODY);
      break;

    case LONG_PAUSE_TYPE: 
      send_notification(LONG_PAUSE_NOTIF_TITLE, LONG_PAUSE_NOTIF_BODY);
      break;
  }
}

void pause_timer(Timer * timer)
{
  timer->paused = 1;
}

void unpause_timer(Timer * timer)
{
  timer->paused = 0;
}

void toggle_pause_timer(Timer * timer)
{
  timer->paused = !timer->paused;
}

void reduce_timer_second_not_paused(Timer * timer)
{
  if(timer->paused != 1)
    timer->seconds = timer->seconds - 1;
}

float minutes_of_timer_type(TimerType type)
{
  switch (type) {
    case POMODORO_TYPE:
      return POMODORO_MINUTES;
    break;
    case SHORT_PAUSE_TYPE:
      return SHORT_PAUSE_MINUTES;
    break;
    case LONG_PAUSE_TYPE:
      return LONG_PAUSE_MINUTES;
    break;
  }
}

void set_timer_seconds_based_on_type(Timer * timer)
{
  timer->seconds = minutes_of_timer_type(timer->type)*SECONDS_IN_MINUTES;
}

void cycle_type(Timer * timer)
{
  switch (timer->type) {
    case POMODORO_TYPE:
      timer->type = SHORT_PAUSE_TYPE;
      timer->pomodoro_count--;
    break;
    case SHORT_PAUSE_TYPE:
      timer->type = POMODORO_TYPE;
    break;
  }
  if (timer->pomodoro_count == 0)
    timer->type = LONG_PAUSE_TYPE;
}

void initialize_timer(Timer *timer)
{
  timer->paused = 0;
  timer->pomodoro_count = 4;
  timer->type = POMODORO_TYPE;
}

void print_time_left(Timer *timer)
{
  int minutes = timer->seconds/60;
  int seconds = timer->seconds%60;

  printf("%02d:%02d\n", minutes,seconds);
}

