#include "preprocess.h"

void ecopeak_preprocess(uint16_t target[4], uint32_t ins) {
    target[0] = target[1] = target[2] = target[3] = 0;
    target[0] = (ins & 0xFC000000) >> 26;
    switch (target[0]) {
    /* 31..26 25..21 20..16 15..11 10....0
       opcode param0 param1 param2 ignored */
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_MULU:
    case OP_DIVU:
    case OP_REM:
    case OP_REMU:
    case OP_AND:
    case OP_OR:
    case OP_XOR:
    case OP_XNOR:
    case OP_SLL:
    case OP_SLR:
    case OP_SAR:
        target[1] = (ins & 0x03E00000) >> 21;
        target[2] = (ins & 0x001F0000) >> 16;
        target[3] = (ins & 0x0000F800) >> 11;
        break;
    /* 31..26 25..21 20..16 15...0
       opcode param0 param1 param2
       31..26 25..21 20..16 15....0
       opcode param0 param1 ignored */
    case OP_ADDI:
    case OP_SUBI:
    case OP_MULI:
    case OP_MULUI:
    case OP_DIVI:
    case OP_DIVUI:
    case OP_REMI:
    case OP_REMUI:
    case OP_ANDI:
    case OP_ORI:
    case OP_XORI:
    case OP_XNORI:
    case OP_SLLI:
    case OP_SLRI:
    case OP_SARI:
    case OP_LDHI:
    case OP_BEQ:
    case OP_BNE:
    case OP_BLE:
    case OP_BLEU:
    case OP_BLT:
    case OP_BLTU:
    case OP_BGE:
    case OP_BGEU:
    case OP_BGT:
    case OP_BGTU:
    case OP_LDW:
    case OP_LDH:
    case OP_LDHU:
    case OP_LDB:
    case OP_LDBU:
    case OP_STW:
    case OP_STH:
    case OP_STB:
    case OP_MVFS:
    case OP_MVTS:
        target[1] = (ins & 0x03E00000) >> 21;
        target[2] = (ins & 0x001F0000) >> 16;
        target[3] = ins & 0x0000FFFF;
        break;
    /* 31..26 25....16 15.....0
       opcode param0_1 param0_0
       31..26 25....0
       opcode ignored */
    case OP_J:
    case OP_JAL:
    case OP_TRAP:
    case OP_RFX:
    case OP_TBS:
    case OP_TBWR:
    case OP_TBRI:
    case OP_TBWI:
        target[1] = (ins & 0x03FF0000) >> 16;
        target[2] = ins & 0x0000FFFF;
        break;
    /* 31..26 25..21 20....0
       opcode param0 ignored */
    case OP_JR:
    case OP_JALR:
        target[1] = (ins & 0x03E00000) >> 21;
    }
}