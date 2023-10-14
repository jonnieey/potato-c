#ifndef SIGNAL_H__
#define SIGNAL_H__

#include <signal.h>
#define SIG_PAUSE		SIGUSR1
#define SIG_UNPAUSE  SIGUSR2
#define SIG_TPAUSE  41
#define SIG_SKIP     42	

#define POTATO_PIDS_DIRECTORY "/tmp/potato-c"
#endif // !SIGNAL_H__

