#ifndef ECOPEAK_READ_BIN_H
#define ECOPEAK_READ_BIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef ECOPEAK_READ_BIN_BUFFER_SIZE
#define ECOPEAK_READ_BIN_BUFFER_SIZE 16 /* MAX 65536!!! */
#endif

/*!
 * \brief Opens a binary file
 * \param filename Filename of the binary file
 * \param _eof_flag Pointer to a boolean that is set to true when the end of file is reached
 * \returns Error code (0=OK, 1=ERROR)
 */
int ecopeak_open_bin(const char*, bool*);

/*!
 * \brief Closes the currently opened binary file
 */
void ecopeak_close_bin();


/*!
 * \brief Reads the next chunk of binary data into a buffer
 * \param buffer Buffer where the file content is copied into
 */
uint32_t* ecopeak_read_bin(uint32_t*);

#ifdef ECOPEAK_BYTESWAP_SUPPORTED
#undef ECOPEAK_BYTESWAP_SUPPORTED
#endif

#endif