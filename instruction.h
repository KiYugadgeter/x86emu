#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "modrm.h"
#include "emulator.h"
#include "emulator_function.h"

void init_instructions();
static void mov_rm32_imm32(Emulator* emu);
static void mov_rm32_r32(Emulator* emu);
static void mov_r32_rm32(Emulator* emu);

static void add_rm32_r32(Emulator* emu);
static void sub_rm32_imm8(Emulator* emu, ModRM* modrm);

static void code_83(Emulator* emu);
static void inc_rm32(Emulator* emu, ModRM* modrm);

void short_jump(Emulator* emu);
void near_jump(Emulator* emu);

static void cmp_rm32_imm8(Emulator* emu, ModRM* modrm);

typedef void instruction_func_t(Emulator*);
extern instruction_func_t* instructions[256];

#endif
