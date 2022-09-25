#include "semaphore.h"

#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



int ecopeak_init_semaphore(ecopeak_semaphore* sem, int val) {
	return sem_init(sem, 0, val) ? 1 : 0;
}

int ecopeak_post_semaphore(ecopeak_semaphore* sem) {
	return sem_post(sem) ? 1 : 0;
}

int ecopeak_wait_semaphore(ecopeak_semaphore* sem) {
	return sem_wait(sem) ? 1 : 0;
}

int ecopeak_destroy_semaphore(ecopeak_semaphore* sem) {
	return sem_destroy(sem) ? 1 : 0;
}



#elif defined(ECOPEAK_PLATFORM_WINDOWS)



int ecopeak_init_semaphore(ecopeak_semaphore* sem, int val) {
	*sem = CreateSemaphore(
		NULL,
		val,
		0xFFFFFFFF,
		NULL);
	return *sem ? 0 : 1;
}

int ecopeak_post_semaphore(ecopeak_semaphore* sem) {
	return ReleaseSemaphore(*sem, 1, NULL) ? 0 : 1;
}

int ecopeak_wait_semaphore(ecopeak_semaphore* sem) {
	return WaitForSingleObject(*sem, INFINITE) == 0xFFFFFFFF ? 1 : 0;
}

int ecopeak_destroy_semaphore(ecopeak_semaphore* sem) {
	return CloseHandle(*sem) ? 1 : 0;
}



#endif