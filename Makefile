OBJS = main.o emulator_function.o instruction.o modrm.o io.o
CC = gcc
.PHONY: all
all : 
	make main
main: $(OBJS)
	$(CC) -g -o main $(OBJS)


%.o: %.c
	$(CC) -I . -g -c -o $@ $<

crt0.o: crt0.asm
	nasm -f elf32 crt0.asm

key.bin: key.asm
	nasm -f bin -o key.bin key.asm


test.o: test.c
	gcc -m32 -fno-pic -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -c test.c

test.bin: test.o crt0.o
	ld -m elf_i386 --entry=start  --oformat=binary -Ttext 0x7c00 -o test.bin crt0.o test.o

.PHONY: testbin
testbin:
	rm -rf test.o
	make test.o
	make test.bin

.PHONY: key
key:
	make key.bin

.PHONY: clean
clean:
	rm -rf *.o *.bin

