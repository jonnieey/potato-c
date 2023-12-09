// Set both notif_title and notif_body to NULL if you want program to have no notifications on event

static const char * notification_basecmd = "herbe '%t' '%d' &> /dev/null & disown";

#define POMODORO_NOTIF_TITLE "Pomodoro"
#define POMODORO_NOTIF_BODY "Time to focus!"

#define SHORT_BREAK_NOTIF_TITLE "Short pause"
#define SHORT_BREAK_NOTIF_BODY "Have a little time for yourself."

#define LONG_BREAK_NOTIF_TITLE "Long pause" 
#define LONG_BREAK_NOTIF_BODY "Take a good long break."


#define PAUSED_NOTIF_TITLE "Paused" 
#define PAUSED_NOTIF_BODY "Timer have been paused."

#define UNPAUSED_NOTIF_TITLE "Unpaused" 
#define UNPAUSED_NOTIF_BODY "Timer have been unpaused."

#define POMODORO_BEFORE_TIME_STRING "PM "
#define SHORT_BREAK_BEFORE_TIME_STRING "SP "
#define LONG_BREAK_BEFORE_TIME_STRING "LP "

#define BEFORE_POMODORO_COUNT_STRING " P "

#define POMODORO_COUNT 4

#define DISOWN_NULL " &> /dev/null & disown"
static const char* ON_POMODORO_START_COMMANDS[] = {
};
static const char* ON_SHORT_BREAK_START_COMMANDS[] = {
};
static const char* ON_LONG_BREAK_START_COMMANDS[] = {
};
static const char* ON_PAUSE_COMMANDS[] = {
};
static const char* ON_UNPAUSE_COMMANDS[] = {
};

#define POMODORO_MINUTES 25
#define SHORT_BREAK_MINUTES 5
#define LONG_BREAK_MINUTES 30
