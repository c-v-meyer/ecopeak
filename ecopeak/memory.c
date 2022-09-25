#include "memory.h"

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
 * \brief Memory pre-allocation thread
 */
static ecopeak_thread ecopeak_prealloc_memory_thread_id;

/*!
 * \brief Used to trigger the next memory pre-allocation
 */
static ecopeak_semaphore ecopeak_prealloc_memory_thread_continue;

/*!
 * \brief Used to prevent the main thread from locking faster than the memory pre-allocation thread
 */
static ecopeak_semaphore ecopeak_prealloc_memory_thread_continued;

/*!
 * \brief Used to lock all shared variables between the main thread and the memory pre-allocation thread
 */
static ecopeak_mutex ecopeak_prealloc_memory_thread_lock;

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
        ecopeak_lock_mutex(&ecopeak_prealloc_memory_thread_lock);
        ecopeak_post_semaphore(&ecopeak_prealloc_memory_thread_continued);
        if (ecopeak_prealloc_memory_thread_break)
            break;
        posix_memalign((void**) &ecopeak_prealloc_memory_block, 16, sizeof(struct ecopeak_memory_block));
        memset(ecopeak_prealloc_memory_block, 0, sizeof(struct ecopeak_memory_block));
        ecopeak_unlock_mutex(&ecopeak_prealloc_memory_thread_lock);
        ecopeak_wait_semaphore(&ecopeak_prealloc_memory_thread_continue);
    }
    return NULL;
}

int ecopeak_init_memory() {
    if (ECOPEAK_EXPECT(ecopeak_init_semaphore(&ecopeak_prealloc_memory_thread_continue, 0), 0))
        goto cancel_routine_1;
    if (ECOPEAK_EXPECT(ecopeak_init_semaphore(&ecopeak_prealloc_memory_thread_continued, 0), 0))
        goto cancel_routine_2;
    if (ECOPEAK_EXPECT(ecopeak_init_mutex(&ecopeak_prealloc_memory_thread_lock), 0))
        goto cancel_routine_3;
    if (ECOPEAK_EXPECT(ecopeak_create_thread(&ecopeak_prealloc_memory_thread_id, &ecopeak_prealloc_memory_thread, ECOPEAK_ULTRA_HIGH_THREAD_PRIORITY), 0)) {
        ecopeak_cleanup_memory();
        return 1;
    }
    return 0;

    cancel_routine_3:
    ecopeak_destroy_mutex(&ecopeak_prealloc_memory_thread_lock);
    cancel_routine_2:
    ecopeak_destroy_semaphore(&ecopeak_prealloc_memory_thread_continued);
    cancel_routine_1:
    ecopeak_destroy_semaphore(&ecopeak_prealloc_memory_thread_continue);
    return 1;
}

void* ecopeak_access_memory(uint32_t addr) {
    uint16_t block = addr >> 16;
    uint16_t sub_address = addr & 0x0000FFFF;
    if (ecopeak_memory[block] == NULL) {
        if (ECOPEAK_EXPECT(ecopeak_wait_semaphore(&ecopeak_prealloc_memory_thread_continued), 0))
            return NULL;
        if (ECOPEAK_EXPECT(ecopeak_lock_mutex(&ecopeak_prealloc_memory_thread_lock), 0))
            return NULL;
        ecopeak_memory[block] = ecopeak_prealloc_memory_block;
        if (ECOPEAK_EXPECT(ecopeak_unlock_mutex(&ecopeak_prealloc_memory_thread_lock), 0))
            return NULL;
        if (ECOPEAK_EXPECT(ecopeak_post_semaphore(&ecopeak_prealloc_memory_thread_continue), 0))
            return NULL;
    }
    return &ecopeak_memory[block]->mem[sub_address];
}

void ecopeak_cleanup_memory() {
    ecopeak_wait_semaphore(&ecopeak_prealloc_memory_thread_continued); 
    ecopeak_lock_mutex(&ecopeak_prealloc_memory_thread_lock);
    ecopeak_prealloc_memory_thread_break = true;
    ecopeak_unlock_mutex(&ecopeak_prealloc_memory_thread_lock);
    ecopeak_post_semaphore(&ecopeak_prealloc_memory_thread_continue);
    ecopeak_join_thread(&ecopeak_prealloc_memory_thread_id);
    ecopeak_destroy_mutex(&ecopeak_prealloc_memory_thread_lock);
    ecopeak_destroy_semaphore(&ecopeak_prealloc_memory_thread_continued);
    ecopeak_destroy_semaphore(&ecopeak_prealloc_memory_thread_continue);
    ecopeak_destroy_thread(&ecopeak_prealloc_memory_thread_id);

    free(ecopeak_prealloc_memory_block);
    for (uint_fast16_t i = 0; i < 16384; i++)
        if (ecopeak_memory[i])
            free(ecopeak_memory[i]);
}
