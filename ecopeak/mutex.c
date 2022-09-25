#include "mutex.h"

#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



int ecopeak_init_mutex(ecopeak_mutex* mutex) {
	*mutex = PTHREAD_MUTEX_INITIALIZER;
	return 0;
}

int ecopeak_lock_mutex(ecopeak_mutex* mutex) {
	return pthread_mutex_lock(mutex) ? 1 : 0;
}

int ecopeak_unlock_mutex(ecopeak_mutex* mutex) {
	return pthread_mutex_unlock(mutex) ? 1 : 0;
}

int ecopeak_destroy_mutex(ecopeak_mutex* mutex) {
	return pthread_mutex_destroy(mutex) ? 1 : 0;
}



#elif defined(ECOPEAK_PLATFORM_WINDOWS)



int ecopeak_init_mutex(ecopeak_mutex* mutex) {
	*mutex = CreateMutex(NULL, FALSE, NULL);
	return *mutex ? 0 : 1;
}

int ecopeak_lock_mutex(ecopeak_mutex* mutex) {
	return WaitForSingleObject(*mutex, INFINITE) == 0xFFFFFFFF ? 0 : 1;
}

int ecopeak_unlock_mutex(ecopeak_mutex* mutex) {
	return ReleaseMutex(*mutex) ? 0 : 1;
}

int ecopeak_destroy_mutex(ecopeak_mutex* mutex) {
	return CloseHandle(*mutex) ? 0 : 1;
}



#endif