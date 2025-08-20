// history.h
#ifndef HISTORY_H
#define HISTORY_H

#include <sys/types.h>

typedef struct {
    pid_t pid;
    char command[256];
    int status;
} Process;

void add_to_history(Process history[], int *count, pid_t pid, const char *command, int status);
void write_history_to_file(Process history[], int count, const char *filename);

#endif
