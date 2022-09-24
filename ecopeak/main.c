#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "opcode.h"
#include "preprocess.h"
#include "read_bin.h"
#include "memory.h"
#include "cpu.h"

int main(void) {
    if (ecopeak_init_memory())
        return 1;
    uint8_t* accessed0 = ecopeak_access_memory(0x0030F140);
    *accessed0 = 123;
    uint8_t* accessed1 = ecopeak_access_memory(0x0030F140);
    //printf("%d\n", *accessed1);
    //sleep(0.001);
    accessed0 = ecopeak_access_memory(0x12344321);
    *accessed0 = 110;
    //printf("%d%d\n", *accessed0, *accessed1);
    ecopeak_init_cpu();
    ecopeak_cleanup_memory();

    uint32_t bin_buffer[ECOPEAK_READ_BIN_BUFFER_SIZE];
    bool eof_flag;
    if (ecopeak_open_bin("./bin/test00.bin", &eof_flag))
        return 1;
    while (!eof_flag) {
        ecopeak_read_bin(bin_buffer);
        for (uint_fast16_t i = 0; i < ECOPEAK_READ_BIN_BUFFER_SIZE; i++) {
            uint16_t unraveled[4];
            ecopeak_preprocess(unraveled, bin_buffer[i]);
            printf("%08x -> %016lx (%s %d %d %d)\n",
                bin_buffer[i],
                *(uint64_t*) unraveled,
                ecopeak_get_opcode_name(unraveled[0]),
                unraveled[1],
                unraveled[2],
                unraveled[3]);
        }
    }
    ecopeak_close_bin();
    return 0;
}