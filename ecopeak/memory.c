#include "memory.h"

/* TODO: Fix <pthread.h> errors */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

struct ecopeak_memory_block {
    uint8_t mem[65536];
};

/*!
 * \brief already pre-allocated memory block
 */
static struct ecopeak_memory_block* ecopeak_prealloc_memory_block = NULL;

/*!
 * \brief array with pointers to all currently used memory blocks
 */
static struct ecopeak_memory_block* ecopeak_memory[16384] = {0};

/*!
 * \brief Attributes for memory pre-allocation thread
 */
static pthread_attr_t ecopeak_prealloc_memory_thread_attr;

/*!
 * \brief ID of memory pre-allocation thread
 */
static pthread_t ecopeak_prealloc_memory_thread_id;

/*!
 * \brief Used to trigger the next memory pre-allocation
 */
static sem_t ecopeak_prealloc_memory_thread_continue;

/*!
 * \brief Used to prevent the main thread from locking faster than the memory pre-allocation thread
 */
static sem_t ecopeak_prealloc_memory_thread_continued;

/*!
 * \brief Used to lock all shared variables between the main thread and the memory pre-allocation thread
 */
static pthread_mutex_t ecopeak_prealloc_memory_thread_lock;

/*!
 * \brief Used to trigger the termination of the memory pre-allocation thread
 */
static bool ecopeak_prealloc_memory_thread_break = false;

/*!
 * \brief Pre-allocates memory in a separate thread
 * \param arg Unused
 * \returns NULL
 */
static void* ecopeak_prealloc_memory_thread(void* arg) {
    while (true) {
        pthread_mutex_lock(&ecopeak_prealloc_memory_thread_lock);
        sem_post(&ecopeak_prealloc_memory_thread_continued);
        if (ecopeak_prealloc_memory_thread_break)
            break;
        posix_memalign((void**) &ecopeak_prealloc_memory_block, 16, sizeof(struct ecopeak_memory_block));
        memset(ecopeak_prealloc_memory_block, 0, sizeof(struct ecopeak_memory_block));
        pthread_mutex_unlock(&ecopeak_prealloc_memory_thread_lock);
        sem_wait(&ecopeak_prealloc_memory_thread_continue);
    }
    return NULL;
}

int ecopeak_init_memory() {
    struct sched_param param;
    if (__builtin_expect(pthread_attr_init(&ecopeak_prealloc_memory_thread_attr), 0))
        goto cancel_routine_1;
    if (__builtin_expect(pthread_attr_getschedparam(&ecopeak_prealloc_memory_thread_attr, &param), 0))
        goto cancel_routine_1;
    param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_attr_setschedparam(&ecopeak_prealloc_memory_thread_attr, &param);

    if (__builtin_expect(sem_init(&ecopeak_prealloc_memory_thread_continue, 0, 0), 0))
        goto cancel_routine_2;
    if (__builtin_expect(sem_init(&ecopeak_prealloc_memory_thread_continued, 0, 0), 0))
        goto cancel_routine_3;
    if (__builtin_expect(pthread_create(&ecopeak_prealloc_memory_thread_id, &ecopeak_prealloc_memory_thread_attr, ecopeak_prealloc_memory_thread, NULL), 0)) {
        ecopeak_cleanup_memory();
        return 1;
    }
    return 0;

    cancel_routine_3:
    sem_destroy(&ecopeak_prealloc_memory_thread_continued);
    cancel_routine_2:
    sem_destroy(&ecopeak_prealloc_memory_thread_continue);
    cancel_routine_1:
    pthread_attr_destroy(&ecopeak_prealloc_memory_thread_attr);
    return 1;
}

void* ecopeak_access_memory(uint32_t addr) {
    uint16_t block = addr >> 16;
    uint16_t sub_address = addr & 0x0000FFFF;
    if (ecopeak_memory[block] == NULL) {
        if (__builtin_expect(sem_wait(&ecopeak_prealloc_memory_thread_continued), 0))
            return NULL;
        if (__builtin_expect(pthread_mutex_lock(&ecopeak_prealloc_memory_thread_lock), 0))
            return NULL;
        ecopeak_memory[block] = ecopeak_prealloc_memory_block;
        if (__builtin_expect(pthread_mutex_unlock(&ecopeak_prealloc_memory_thread_lock), 0))
            return NULL;
        if (__builtin_expect(sem_post(&ecopeak_prealloc_memory_thread_continue), 0))
            return NULL;
        __builtin_prefetch(ecopeak_memory[block], 1, 2);
    }
    return &ecopeak_memory[block]->mem[sub_address];
}

void ecopeak_cleanup_memory() {
    sem_wait(&ecopeak_prealloc_memory_thread_continued); 
    pthread_mutex_lock(&ecopeak_prealloc_memory_thread_lock);
    ecopeak_prealloc_memory_thread_break = true;
    pthread_mutex_unlock(&ecopeak_prealloc_memory_thread_lock);
    sem_post(&ecopeak_prealloc_memory_thread_continue);
    pthread_join(ecopeak_prealloc_memory_thread_id, NULL);
    pthread_mutex_destroy(&ecopeak_prealloc_memory_thread_lock);
    sem_destroy(&ecopeak_prealloc_memory_thread_continued);
    sem_destroy(&ecopeak_prealloc_memory_thread_continue);
    pthread_attr_destroy(&ecopeak_prealloc_memory_thread_attr);

    free(ecopeak_prealloc_memory_block);
    for (uint_fast16_t i = 0; i < 16384; i++)
        if (ecopeak_memory[i])
            free(ecopeak_memory[i]);
}

#pragma GCC diagnostic pop