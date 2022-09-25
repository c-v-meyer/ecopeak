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
_Success_(return == 0) int ecopeak_init_semaphore(_Outptr_ ecopeak_semaphore*, _In_ int);

/*!
 * \brief Increments a semaphore
 * \attr sem Pointer to the semaphore to be incremented
 * \returns Status code (0=OK, 1=ERROR)
 */
_Success_(return == 0) int ecopeak_post_semaphore(_In_ ecopeak_semaphore*);

/*!
 * \brief Decrements a semaphore
 * \attr sem Pointer to the semaphore to be decremented
 * \returns Status code (0=OK, 1=ERROR)
 */
_Success_(return == 0) int ecopeak_wait_semaphore(_In_ ecopeak_semaphore*);

/*!
 * \brief Destroys a semaphore
 * \attr sem Pointer to the semaphore to be destroyed
 * \returns Status code (0=OK, 1=ERROR)
 */
_Success_(return == 0) int ecopeak_destroy_semaphore(_In_ ecopeak_semaphore*);

#endif