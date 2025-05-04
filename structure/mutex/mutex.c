//
// Created by rodrigo on 5/4/25.
//

#include "mutex.h"

bool init_mutex(Mutex *mutex)
{
#ifdef _WIN32
    mutex->handle = CreateMutex(NULL, FALSE, NULL);
    if (mutex->handle == NULL) {
        return FALSE; // Failed to create mutex
    }
#else
    if (pthread_mutex_init(&mutex->handle, NULL) != 0) {
        return FALSE; // Failed to initialize mutex
    }
#endif
    return TRUE; // Success
}

bool lock_mutex(Mutex *mutex)
{
#ifdef _WIN32
    DWORD wait_result = WaitForSingleObject(mutex->handle, INFINITE);
    if (wait_result != WAIT_OBJECT_0) {
        return FALSE; // Failed to acquire the mutex
    }
#else
    if (pthread_mutex_lock(&mutex->handle) != 0) {
        return FALSE; // Failed to lock the mutex
    }
#endif
    return TRUE; // Success
}
bool unlock_mutex(Mutex *mutex)
{
#ifdef _WIN32
    if (!ReleaseMutex(mutex->handle)) {
        return FALSE; // Failed to release the mutex
    }
#else
    if (pthread_mutex_unlock(&mutex->handle) != 0) {
        return FALSE; // Failed to unlock the mutex
    }
#endif
    return TRUE; // Success
}
bool destroy_mutex(Mutex *mutex)
{
#ifdef _WIN32
    if (!CloseHandle(mutex->handle)) {
        return FALSE; // Failed to close the mutex handle
    }
#else
    if (pthread_mutex_destroy(&mutex->handle) != 0) {
        return FALSE; // Failed to destroy the mutex
    }
#endif
    return TRUE; // Success
}