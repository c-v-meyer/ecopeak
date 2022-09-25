#ifndef ECOPEAK_SEMAPHORE_H
#define ECOPEAK_SEMAPHORE_H

#include "platform.h"
#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



#include <semaphore.h>

/*!
 * \brief Platform independent semaphore
 */
typedef sem_t ecopeak_semaphore;



#elif defined(ECOPEAK_PLATFORM_WINDOWS)



#include <windows.h>

/*!
 * \brief Platform independent semaphore
 */
typedef HANDLE ecopeak_semaphore;



#else
#error "semaphore.h: This platform is currently not supported"
#endif

/*!
 * \brief Initializes a semaphore
 * \attr sem Pointer to the semaphore to be initialized
 * \attr val Initial value
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_init_semaphore(ecopeak_semaphore*, int);

/*!
 * \brief Increments a semaphore
 * \attr sem Pointer to the semaphore to be incremented
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_post_semaphore(ecopeak_semaphore*);

/*!
 * \brief Decrements a semaphore
 * \attr sem Pointer to the semaphore to be decremented
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_wait_semaphore(ecopeak_semaphore*);

/*!
 * \brief Destroys a semaphore
 * \attr sem Pointer to the semaphore to be destroyed
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_destroy_semaphore(ecopeak_semaphore*);

#endif