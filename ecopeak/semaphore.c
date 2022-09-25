#include "semaphore.h"

#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



int ecopeak_init_semaphore(ecopeak_semaphore* sem, int val) {
	if (ECOPEAK_EXPECT(sem_init(sem, 0, val), 0)) {
		ecopeak_destroy_semaphore(sem);
		return 1;
	}
	return 0;
}

int ecopeak_post_semaphore(ecopeak_semaphore* sem) {
	return ECOPEAK_EXPECT(sem_post(sem), 0) ? 1 : 0;
}

int ecopeak_wait_semaphore(ecopeak_semaphore* sem) {
	return ECOPEAK_EXPECT(sem_wait(sem), 0) ? 1 : 0;
}

int ecopeak_destroy_semaphore(ecopeak_semaphore* sem) {
	return ECOPEAK_EXPECT(sem_destroy(sem), 0) ? 1 : 0;
}



#elif defined(ECOPEAK_PLATFORM_WINDOWS)



int ecopeak_init_semaphore(ecopeak_semaphore* sem, int val) {
	*sem = CreateSemaphore(
		NULL,
		val,
		0xFFFFFFFF,
		NULL);
	if (ECOPEAK_EXPECT(!*sem, 0))
		return 0;
	ecopeak_destroy_semaphore(sem);
	return 1;
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