#ifndef ECOPEAK_PREPROCESS_H
#define ECOPEAK_PREPROCESS_H

#include <stdint.h>
#include <string.h>
#include "opcode.h"

/*!
 * Takes in a word and unravels
 * it into its individual parameters
 * Only exceptions: J and JAL
 * (Parameter is bigger than 16 bits)
 * \brief Unravels word-size instruction into 4 half-word parameters
 * \param target half-word result array of length 4
 * \param ins instruction to be unraveled
 */
void ecopeak_preprocess(uint16_t*, uint32_t);

#endif