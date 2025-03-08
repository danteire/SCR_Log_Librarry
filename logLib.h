#ifndef LOGLIB_H
#define LOGLIB_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <errno.h>

typedef enum{
    MIN,
    STANDARD,
    MAX
}log_level_t;

void init_logger();
void write_log(const char *message, log_level_t level);
void cleanUpProcesses(); // :)

#endif //LOGLIB_H