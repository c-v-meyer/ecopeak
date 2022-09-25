#ifndef ECOPEAK_THREAD_H
#define ECOPEAK_THREAD_H

#include "expect.h"
#include "platform.h"
#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



#include <pthread.h>
#include <sched.h>
#include <stdbool.h>

/*!
 * \brief Platform independent thread
 */
typedef struct {
	pthread_t thread;
	pthread_attr_t thread_attr;
	bool normal_priority;
} ecopeak_thread;

/*!
 * \brief Thread function return type
 */
typedef void* ecopeak_thread_return_type;

#define ECOPEAK_THREAD_RETURN_OK NULL



#elif defined(ECOPEAK_PLATFORM_WINDOWS)


#include <windows.h>

/*!
 * \brief Platform independent thread
 */
typedef struct {
	HANDLE hThread;
	DWORD dwThreadId;
} ecopeak_thread;

/*!
 * \brief Thread function return type
 */
typedef DWORD ecopeak_thread_return_type;

#define ECOPEAK_THREAD_RETURN_OK 0



#else
#error "thread.h: This platform is currently not supported"
#endif

/*!
 * \brief Priority attribute of a thread
 */
enum ecopeak_thread_priority {
	ECOPEAK_ULTRA_LOW_THREAD_PRIORITY,
	ECOPEAK_VERY_LOW_THREAD_PRIORITY,
	ECOPEAK_LOW_THREAD_PRIORITY,
	ECOPEAK_NORMAL_THREAD_PRIORITY,
	ECOPEAK_HIGH_THREAD_PRIORITY,
	ECOPEAK_VERY_HIGH_THREAD_PRIORITY,
	ECOPEAK_ULTRA_HIGH_THREAD_PRIORITY
};

/*!
 * \brief Creates a thread
 * \arg thread Pointer to the thread to be created
 * \arg thread_func Pointer to the function that shall be executed in a separate thread
 * \arg thread_priority Priority of the thread
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_create_thread(ecopeak_thread*, ecopeak_thread_return_type (*)(void*), enum ecopeak_thread_priority);

/*!
 * \brief Joins a separate thread with the thread of the callee
 * \arg thread Pointer to the thread to be joined with
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_join_thread(ecopeak_thread*);

/*!
 * \brief Destroys a thread
 * \arg thread Pointer to the thread to be destroyed
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_destroy_thread(ecopeak_thread*);

#endif