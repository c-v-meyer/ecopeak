#include "mmu.h"

/*!
 * Maps 32 20-bit page numbers to 1 page frame number each
 * \brief Translation Lookaside Buffer
 */
static uint32_t ecopeak_tlb[32][2];

void ecopeak_init_mmu() {
    for (uint_fast8_t i = 0; i < 32; i++)
        ecopeak_tlb[i][0] = 0x000C0000 + i;
}

uint32_t ecopeak_virtual_to_physical(uint32_t addr) {
    if (addr < 0xC0000000) { /* page-mapped space */
        uint32_t page_number = addr >> 12;
        for (uint_fast8_t i = 0; i < 32; i++) {
            if (ecopeak_tlb[i][0] == page_number) {
                return (ecopeak_tlb[i][1] << 12) | (addr & 0x00000FFF);
            }
        }
        /* TODO: Throw TLB Miss Fault */
        return 0;
    } else { /* direct-mapped space */
        return addr - 0xC0000000;
    }
}