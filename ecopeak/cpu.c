#include "cpu.h"

/*!
 * \brief Program counter register
 */
static uint32_t ecopeak_pc = 0xE0000000;

/*!
 * \brief Processor status word register
 */
static uint32_t ecopeak_psw = 0;

/*!
 * \brief Translation lookaside buffer index register
 */
static uint32_t ecopeak_tlb_index;

/*!
 * \brief Translation lookaside buffer entry high register
 */
static uint32_t ecopeak_tlb_entry_high;

/*!
 * \brief Translation lookaside buffer entry low register
 */
static uint32_t ecopeak_tlb_entry_low;

/*!
 * \brief Translation lookaside buffer bad address register
 */
static uint32_t ecopeak_tlb_bad_address;

/*!
 * \brief General purpose registers
 */
static uint32_t ecopeak_regs[32];

/*!
 * \brief Converts an unsigned byte value into a signed byte value
 */
static int8_t ecopeak_sign8(uint8_t val) {
    int8_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Converts a signed byte value into an unsigned byte value
 */
static uint8_t ecopeak_unsign8(int8_t val) {
    uint8_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Converts an unsigned half-word value into a signed half-word value
 */
static int16_t ecopeak_sign16(uint16_t val) {
    int16_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Converts a signed half-word value into an unsigned half-word value
 */
static uint16_t ecopeak_unsign16(int16_t val) {
    uint16_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Converts an unsigned word value into a signed word value
 */
static int32_t ecopeak_sign32(uint32_t val) {
    int32_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Converts a signed word value into an unsigned word value
 */
static uint32_t ecopeak_unsign32(int32_t val) {
    uint32_t ret_val = 0;
    return ret_val | val;
}

/*!
 * \brief Zero-extends an unsigned byte value to a word
 * \param val Value to be extended
 * \returns Extended value
 */
static uint32_t ecopeak_zeroext32_8(uint8_t val) {
    return 0x00000000 | val;
}

/*!
 * \brief Zero-extends an unsigned half-word value to a word
 * \param val Value to be extended
 * \returns Extended value
 */
static uint32_t ecopeak_zeroext32_16(uint16_t val) {
    return 0x00000000 | val;
}

/*!
 * \brief Sign-extends an unsigned byte value to a word
 * \param val Value to be extended
 * \returns Extended value
 */
static uint32_t ecopeak_signext32_8(uint8_t val) {
    uint32_t ret_val = 0x00000000 | val;
    if (val & 0x80)
        ret_val |= 0xFFFFFF00;
    return ret_val;
}

/*!
 * \brief Sign-extends an unsigned half-word value to a word
 * \param val Value to be extended
 * \returns Extended value
 */
static uint32_t ecopeak_signext32_16(uint16_t val) {
    uint32_t ret_val = 0x00000000 | val;
    if (val & 0x8000)
        ret_val |= 0xFFFF0000;
    return ret_val;
}

void ecopeak_init_cpu() {
    ecopeak_regs[0] = 0;
    srand(time(NULL));
    for (uint_fast8_t i = 1; i < 32; i++)
        ecopeak_regs[i] = (uint32_t) rand();
}