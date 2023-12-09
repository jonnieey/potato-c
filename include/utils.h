#ifndef UTILS_H__
#define UTILS_H__
#include <stddef.h>
void recursive_mkdir(char *path);
void send_notification(char *title, char *description);
size_t int_length(int);
int min(int a, int b);
char toggle_lower(char ch);
char * resolve_format(char const *format, char * handler(void *, char), void * args);
#define LENGTH(X) (sizeof X / sizeof X[0])
#endif
