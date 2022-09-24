#ifndef ECOPEAK_OPCODE_H
#define ECOPEAK_OPCODE_H

/*
Clever trick I found on stackoverflow
to define an enum and a string array
with the names of all enum values at once
*/
#define ECOPEAK_OPCODES \
    C(ADD)              \
    C(ADDI)             \
    C(SUB)              \
    C(SUBI)             \
    C(MUL)              \
    C(MULI)             \
    C(MULU)             \
    C(MULUI)            \
    C(DIV)              \
    C(DIVI)             \
    C(DIVU)             \
    C(DIVUI)            \
    C(REM)              \
    C(REMI)             \
    C(REMU)             \
    C(REMUI)            \
    C(AND)              \
    C(ANDI)             \
    C(OR)               \
    C(ORI)              \
    C(XOR)              \
    C(XORI)             \
    C(XNOR)             \
    C(XNORI)            \
    C(SLL)              \
    C(SLLI)             \
    C(SLR)              \
    C(SLRI)             \
    C(SAR)              \
    C(SARI)             \
    C(_NDEF)            \
    C(LDHI)             \
    C(BEQ)              \
    C(BNE)              \
    C(BLE)              \
    C(BLEU)             \
    C(BLT)              \
    C(BLTU)             \
    C(BGE)              \
    C(BGEU)             \
    C(BGT)              \
    C(BGTU)             \
    C(J)                \
    C(JR)               \
    C(JAL)              \
    C(JALR)             \
    C(TRAP)             \
    C(RFX)              \
    C(LDW)              \
    C(LDH)              \
    C(LDHU)             \
    C(LDB)              \
    C(LDBU)             \
    C(STW)              \
    C(STH)              \
    C(STB)              \
    C(MVFS)             \
    C(MVTS)             \
    C(TBS)              \
    C(TBWR)             \
    C(TBRI)             \
    C(TBWI)
#define C(x) OP_##x,

/*!
 * \brief Enum with all opcodes
 */
enum ecopeak_opcode { ECOPEAK_OPCODES _END };

#undef C

/*!
 * \brief Returns the name of an opcode
 * \param opcode Opcode to get the name of
 * \returns Name of the opcode
 */
const char* ecopeak_get_opcode_name(enum ecopeak_opcode);

#endif