#ifndef FT_NM_H
#define FT_NM_H

#include "stdio.h"
#include <elf.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_32bits {
	Elf32_Ehdr *header;
} t_32bits;

typedef struct s_64bits {
	Elf64_Ehdr *header;
} t_64bits;

typedef union {
	t_32bits u_32bits;
	t_64bits u_64bits;
} u_Nbits;

typedef struct s_nm {
	u_Nbits infoBits;
	bool is64Bits;
	char *mapped;
} t_nm;

// main.c
int main(int argc, char **argv);

#endif // !FT_NM_H
