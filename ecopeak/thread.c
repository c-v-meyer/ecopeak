#include "thread.h"

#if defined(ECOPEAK_PLATFORM_UNIX_LIKE)



int ecopeak_create_thread(ecopeak_thread* thread, void* (*thread_func)(void*), enum ecopeak_thread_priority thread_priority) {
	if (thread_priority == ECOPEAK_NORMAL_THREAD_PRIORITY) {
		thread->normal_priority = true;
		return pthread_create(&thread->thread, NULL, thread_func, NULL) ? 1 : 0;
	}

	thread->normal_priority = false;
	if (ECOPEAK_EXPECT(pthread_attr_init(&thread->thread_attr), 0))
		goto cancel_routine_1;
	struct sched_param param;
	if (ECOPEAK_EXPECT(pthread_attr_getschedparam(&thread->thread_attr), 0))
		goto cancel_routine_1;
	param.sched_priority = sched_get_priority_max(SCHED_FIFO) / 6 * (uint32_t) thread_priority;
	if (ECOPEAK_EXPECT(pthread_attr_setschedparam(&thread->thread_attr, &param), 0))
		goto cancel_routine_1;

	if (ECOPEAK_EXPECT(pthread_create(&thread->thread, &thread->thread_attr, thread_func, NULL), 0))
		goto cancel_routine_2;

    cancel_routine_2:
	pthread_destroy(&thread->thread);
    cancel_routine_1:
	pthread_attr_destroy(&thread->thread_attr);
	return 1;
}

int ecopeak_join_thread(ecopeak_thread* thread) {
	return pthread_join(ecopeak_thread->thread, NULL) ? 1 : 0;
}

int ecopeak_destroy_thread(ecopeak_thread* thread) {
	if (!thread->normal_priority)
		return pthread_attr_destroy(&thread->thread_attr) ? 1 : 0;
	return 0;
}



#elif defined(ECOPEAK_PLATFORM_WINDOWS)



int ecopeak_create_thread(ecopeak_thread* thread, void* (*thread_func)(void*), enum ecopeak_thread_priority thread_priority) {
	thread->hThread = CreateThread(NULL, 0, thread_func, NULL, 0, &thread->dwThreadId);
	if (ECOPEAK_EXPECT(!thread->hThread, 0)) {
		int nPriority;
		switch (thread_priority) {
		case ECOPEAK_ULTRA_LOW_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_IDLE;
			break;
		case ECOPEAK_VERY_LOW_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_LOWEST;
			break;
		case ECOPEAK_LOW_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		case ECOPEAK_NORMAL_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_NORMAL;
			break;
		case ECOPEAK_HIGH_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case ECOPEAK_VERY_HIGH_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_HIGHEST;
			break;
		case ECOPEAK_ULTRA_HIGH_THREAD_PRIORITY:
			nPriority = THREAD_PRIORITY_TIME_CRITICAL;
			break;
		default:
			nPriority = THREAD_PRIORITY_NORMAL;
		}
		if (ECOPEAK_EXPECT(!SetThreadPriority(thread->hThread, nPriority), 0))
			return 0;
	}
	ecopeak_destroy_thread(thread);
	return 1;
}

int ecopeak_join_thread(ecopeak_thread* thread) {
	return WaitForSingleObject(thread->hThread, INFINITE) == 0xFFFFFFFF ? 1 : 0;
}

int ecopeak_destroy_thread(ecopeak_thread* thread) {
	return CloseHandle(thread->hThread) ? 1 : 0;
}



#endif