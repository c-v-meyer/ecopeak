#ifndef ECOPEAK_MMU_H
#define ECOPEAK_MMU_H

#include <stdint.h>

/*!
 * \brief Initializes the memory management unit
 */
void ecopeak_init_mmu();

/*!
 * \brief Maps a virtual to a physical memory address
 * \param addr Virtual address to be mapped
 * \returns Physical address
 */
uint32_t ecopeak_virtual_to_physical(uint32_t);

#endif