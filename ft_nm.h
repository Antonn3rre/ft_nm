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
	Elf32_Phdr *program;
	Elf32_Shdr *section;
	Elf32_Shdr *symtab;
	Elf32_Shdr *strtab;
} t_32bits;

typedef struct s_64bits {
	Elf64_Ehdr *header;
	Elf64_Phdr *program;
	Elf64_Shdr *section;
	Elf64_Shdr *symtab;
	Elf64_Shdr *strtab;
} t_64bits;

typedef union {
	t_32bits u_32bits;
	t_64bits u_64bits;
} u_Nbits;

typedef struct s_nm {
	u_Nbits infoBits;
	bool is64Bits;
	char *mapped;
	size_t fileSize;
	bool hasProgram;
	bool hasSection;
} t_nm;

// main.c
int main(int, char **);

// init.c
int init(int, char **, t_nm *);

// findHeader.c
int findSymtabHeader(t_nm *info);

// printInfo.c
int printInfo(t_nm *info);

#endif // !FT_NM_H
