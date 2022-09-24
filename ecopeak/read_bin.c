#include "read_bin.h"

static FILE* bin_file = NULL;
static bool* eof_flag;

int ecopeak_open_bin(const char* filename, bool* _eof_flag) {
    eof_flag = _eof_flag;
    *eof_flag = false;
    bin_file = fopen(filename, "rb");
    if (!bin_file)
        return 1;
    return 0;
}

void ecopeak_close_bin() {
    fclose(bin_file);
}

uint32_t* ecopeak_read_bin(uint32_t* buffer) {
    uint32_t tmp[ECOPEAK_READ_BIN_BUFFER_SIZE] = {0};
    fread(tmp, ECOPEAK_READ_BIN_BUFFER_SIZE << 2, 1, bin_file);
    for (uint_fast16_t i = 0; i < ECOPEAK_READ_BIN_BUFFER_SIZE; i++) {
        buffer[i] = __builtin_bswap32(tmp[i]);
    }
    *eof_flag = feof(bin_file);
    return buffer;
}