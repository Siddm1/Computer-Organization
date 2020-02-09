# makefile for the cs3421_emul assignment

# These variables control the specifics of the compilation
CC = gcc
CFLAGS = -g -ggdb -std=c11 -pedantic -Wall -Wextra -O1
LDFLAGS = -lm

# When you type "make", it will default to trying to build all the programs
default: cs3421_emul
	
# To build just the cs3421_emul executable, type "make cs3421_emul"
#cs3421_emul: cs3421_emul.c cs3421_clock.o cs3421_memory.o cs3421_cpu.o
cs3421_emul: cs3421_emul.o cs3421_clock.o cs3421_memory.o cs3421_cpu.o cs3421_imemory.o
	${CC} ${CFLAGS} cs3421_clock.o cs3421_cpu.o cs3421_memory.o cs3421_emul.o cs3421_imemory.o -o cs3421_emul ${LDFLAGS}

# Builds just the object file for the cs3421_clock device data type
cs3421_clock.o: cs3421_clock.c cs3421_clock.h
	${CC} ${CFLAGS} -c cs3421_clock.c

# Builds just the object file for the cs3421_cpu device data type
cs3421_cpu.o: cs3421_cpu.c cs3421_cpu.h
	${CC} ${CFLAGS} -c cs3421_cpu.c

# Builds just the object file for the cs3421_memory device data type
cs3421_memory.o: cs3421_memory.c cs3421_memory.h
	${CC} ${CFLAGS} -c cs3421_memory.c

	# Builds just the object file for the cs3421_imemory device data type
cs3421_imemory.o: cs3421_imemory.c cs3421_imemory.h
	${CC} ${CFLAGS} -c cs3421_imemory.c

cs3421_emul.o: cs3421_emul.c 
	${CC} ${CFLAGS} -c cs3421_emul.c

run: cs3421_emul
	./cs3421_emul
debug: cs3421_emul
	valgrind --leak-check=full --show-leak-kinds=all ./cs3421_emul Sample1_input.txt
clean: 
	rm -f cs3421_emul.o cs3421_clock.o cs3421_cpu.o cs3421_memory.o cs3421_imemory.o
	
