#ifndef ECOPEAK_MEMORY_H
#define ECOPEAK_MEMORY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <string.h>

/*!
 * \brief memory block of size 65536
 */
struct ecopeak_memory_block;

/*!
 * \brief Initializes the memory module
 * \returns Status code (0=OK, 1=ERROR)
 */
int ecopeak_init_memory();

/*!
 * Access memory at a specific address
 * WITHOUT caring about alignment
 * \brief Access memory at a specific address
 * \param addr Memory address
 * \returns Pointer to location in memory
 */
void* ecopeak_access_memory(uint32_t addr);

/*!
 * \brief Free all used memory
 */
void ecopeak_cleanup_memory();

#endif
