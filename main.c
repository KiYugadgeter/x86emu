#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#include "emulator.h"
#include "emulator_function.h"
#include "instruction.h"

char* registers_name[] = {
    "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"
};

static void read_binary(Emulator* emu, const char* filename) {
    FILE* binary;
    binary = fopen(filename, "rb");
    
    if (binary == NULL) {
        printf("cannot open %s file", filename);
        exit(1);
    }
    
    fread(emu->memory+0x7c00, 1, 0x200, binary);
    fclose(binary);
}

static Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp) {
    Emulator* emu = malloc(sizeof(Emulator));
    emu->memory = malloc(size);
    if (emu == NULL) {
        puts("malloc failed");
        return NULL;
    }
    memset(emu->registers, 0, sizeof(emu->registers));
    emu->eip = eip;
    emu->registers[ESP] = esp;
    return emu;
}

static void destroy_emu(Emulator* emu) {
    free(emu->memory);
    free(emu);
}

static void dump_registers(Emulator* emu) {
    int i;
    for (i = 0; i < REGISTERS_COUNT; i++) {
        printf("%s=%08x\n", registers_name[i], emu->registers[i]);
    }
    printf("EIP = %08x\n", emu->eip);
}

int opt_remove_at(int argc, char* argv[], int index) {
    if (index < 0 || argc <= index) {
        return argc;
    }
    else {
        int i = index;
        for (; i < argc - 1; i++) {
            argv[i] = argv[i+1];
        }
        argv[i] = NULL;
        return argc - 1;
    }
}


int main(int argc, char* argv[]) {
    FILE* binary;
    Emulator* emu;
    int i;
    int quiet = 0;
    
    i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-q") == 0) {
            quiet = 1;
            argc = opt_remove_at(argc, argv, i);
        }
        else {
            i++;
        }
    }
    if (argc != 2) {
        printf("usage: px86 filename\n");
        return 1;
    }
    
    emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);
    read_binary(emu, argv[1]);
    init_instructions();
    
    while (emu->eip < MEMORY_SIZE) {
        uint8_t code = get_code8(emu, 0);
        if (!quiet) {
            uint32_t esi = get_register32(emu, ESI);
            uint8_t al = get_register8(emu, AL);
            printf("EIP = %X, ESI = %X, AL = %X, Code = %02X\n", emu->eip, esi, al, code);
        }
        if (instructions[code] == NULL) {
            printf("\n\nNot Implemented: %x : eip=%x\n", code, emu->eip - 0x7c00);
            break;
        }
        
        instructions[code](emu);
        if (emu->eip == 0x00) {
            printf("\n\nend of program.\n\n");
            break;
        }
    }
    dump_registers(emu);
    //dump_local_variables(emu);
    destroy_emu(emu);
    return 0;
}
