#include "opcode.h"

#define C(x) "OP_"#x,

/*!
 * \brief Array of all opcode names (index with corresponding enum value)
 */
static const char* const ecopeak_opcode_names[] = { ECOPEAK_OPCODES "OP__END" };

const char* ecopeak_get_opcode_name(enum ecopeak_opcode opcode) {
    return ecopeak_opcode_names[opcode];
}

#undef C