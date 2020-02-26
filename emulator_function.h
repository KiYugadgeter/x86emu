#ifndef EMULATOR_FUNCTION_H
#define EMULATOR_FUNCTION_H

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "emulator.h"

#define MEMORY_SIZE (1024 * 1024)

#define CARRY_FLAG (1)
#define ZERO_FLAG (1 << 6)
#define SIGN_FLAG (1 << 7)
#define OVERFLOW_FLAG (1 << 11)

#define DECLARE_IS(flag) \
    extern int is_ ## flag(Emulator* emu);

DECLARE_IS(carry)
DECLARE_IS(overflow)
DECLARE_IS(sign)
DECLARE_IS(zero)


static Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp);
static void destroy_emu(Emulator* emu);
static void dump_registers(Emulator* emu);

void dump_local_variables(Emulator* emu);
void update_eflags_sub(Emulator* emu, uint32_t v1, uint32_t v2, uint64_t result);

uint32_t get_code8(Emulator* emu, int index);
uint32_t get_sign_code8(Emulator* emu, int index);
uint32_t get_code32(Emulator* emu, int index);
int32_t get_sign_code32(Emulator* emu, int index);
uint32_t get_register32(Emulator* emu, int index);
void set_register32(Emulator* emu, int index, uint32_t value);
void set_memory8(Emulator* emu, uint32_t address, uint32_t value);
void set_memory32(Emulator* emu, uint32_t address, uint32_t value);
uint32_t get_memory8(Emulator* emu, uint32_t address);
uint32_t get_memory32(Emulator* emu, uint32_t address);
uint8_t get_register8(Emulator* emu, int index);
void set_register8(Emulator* emu, int index, uint8_t value);
void push32(Emulator* emu, uint32_t value);
uint32_t pop32(Emulator* emu);

#endif
