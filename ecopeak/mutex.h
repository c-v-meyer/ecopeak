#ifndef ECOPEAK_MUTEX_H
#define ECOPEAK_MUTEX_H

#include "platform.h"
#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



#include <pthread.h>

/*!
 * \brief Platform independent mutex
 */
typedef pthread_mutex_t ecopeak_mutex;


#elif defined(ECOPEAK_PLATFORM_WINDOWS)



#include <windows.h>

/*!
 * \brief Platform independent mutex
 */
typedef HANDLE ecopeak_mutex;


#else
#error "mutex.h: This platform is currently not supported"
#endif

/*!
 * \brief Initializes a mutex
 * \attr mutex Pointer to the mutex to be initialized
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_init_mutex(ecopeak_mutex*);

/*!
 * \brief Locks a mutex
 * \attr mutex Pointer to the mutex to be locked
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_lock_mutex(ecopeak_mutex*);

/*!
 * \brief Unlocks a mutex
 * \attr mutex Pointer to the mutex to be unlocked
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_unlock_mutex(ecopeak_mutex*);

/*!
 * \brief Destroys a mutex
 * \attr mutex Pointer to the mutex to be destroyed
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_lock_mutex(ecopeak_mutex*);

#endif