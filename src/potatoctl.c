#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#include "../config.h"
#include "../include/client.h"
#include "../include/timer.h"

#define case_index(ch,function) case ch:\
{\
  int index = EVERY_MEMBER;\
  if (optarg != NULL)\
    sscanf(optarg, "%d", &index);\
  run_function_on_pid_file_index(function, index);\
  break;\
}

void handle_list_pid_files(char * pid_str, int index)
{
  int pid = atoi(pid_str);
  Timer timer = get_local_timer_from_pid(pid);
  if (timer.type == NULL_TYPE) {
    printf("%d\t%s\n", index, pid_str);
    return;
  }

  char * is_paused = timer.paused ? "Yes" : "No";

  char * time_left = Timer_time_left(&timer);
  printf("%d\t%s\t%s\t%s\t%d\n", index, pid_str, time_left, is_paused, timer.pomodoro_count);
  free(time_left);
}

void get_type(char *pid_str, int index)
{
  printf("%d\n",send_socket_request_return_num(REQ_TYPE,atoi(pid_str), "127.0.0.1"));
}

void get_seconds(char *pid_str, int index)
{
  printf("%d\n", send_socket_request_return_num(REQ_SECONDS,atoi(pid_str), "127.0.0.1"));
}

char * print_format = NULL;
void get_timer_one_time(char *pid_str, int index)
{
  Timer timer = get_local_timer_from_pid(atoi(pid_str));
  if (timer.type == NULL_TYPE)
    return;

  Timer_print_format(&timer, print_format);
}

void get_timer_each_second(char *pid_str, int index)
{
  Timer timer;
  while (1) {
    timer = get_local_timer_from_pid(atoi(pid_str));
    if (timer.type == NULL_TYPE)
      break;

    Timer_print_format(&timer, print_format);
    sleep(1);
  }
}

void list_all_timers()
{
  if (get_pids_length()) {
    puts("INDEX\tPID\tTIME\tPAUSED\tPOMODOROS");
    run_function_on_pid_file_index(handle_list_pid_files, EVERY_MEMBER);
  }
}

int main(int argc, char *argv[])
{   
  if (argc < 2) {
    list_all_timers();
    return EXIT_SUCCESS;
  }
  int ch;
  Timer timer = {.type=NULL_TYPE};
  _Bool loop_flag = 0;
  char server_address[16];
  int port = 0;
  while ((ch = getopt(argc, argv, "1::T::S::c::lu::L::s::p::t::q::d::i::I::D::r::a:A:")) != -1) {
    switch (ch) {
      case 'l': 
        list_all_timers();
      break;
      case 'A':
        loop_flag = 1;
      case 'a': {
        int status = sscanf(optarg, "%15[^:]:%d", server_address, &port);
        if (status != 2) {
          puts("Socket address is invalid");
          exit(1);
        }
      }
      break;

      case_index('c', handle_remove_pid);
      case_index('p', handle_pause);
      case_index('u', handle_unpause);
      case_index('t', handle_toggle_pause);
      case_index('q', handle_quit);
      case_index('s', handle_skip);
      case_index('i', handle_increase_10sec);
      case_index('d', handle_decrease_10sec);
      case_index('I', handle_increase_pomodoro_count);
      case_index('D', handle_decrease_pomodoro_count);
      case_index('r', handle_reset_pomodoro);
      case_index('T', get_timer_each_second);
      case_index('1', get_timer_one_time);
    }
  }
  read_format_from_optind(argc, argv, &print_format);
  if (port) {
    while (1) {
      timer = get_timer_from_port(port,server_address);
      if (timer.type == NULL_TYPE) {
        puts("There is no timer on the specified address");
        exit(EXIT_FAILURE);
      }
      Timer_print_format(&timer, print_format);
      if (!loop_flag )
        break;
      sleep(1);
    } 
  }
  return EXIT_SUCCESS;
}
