//
// Created by rodrigo on 5/4/25.
//

#ifndef MUTEX_H
#define MUTEX_H

#ifndef BOOL_H
#include "../../types/bool.h"
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

// Define a portable mutex structure
typedef struct {
#ifdef _WIN32
    HANDLE hadle;  // Windows mutex handle
#else
    pthread_mutex_t handle;  // POSIX mutex
#endif
} Mutex;

bool init_mutex(Mutex *mutex);
bool lock_mutex(Mutex *mutex);
bool unlock_mutex(Mutex *mutex);
bool destroy_mutex(Mutex *mutex);

#endif //MUTEX_H
