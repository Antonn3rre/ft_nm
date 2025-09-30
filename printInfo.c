#include "ft_nm.h"
#include <elf.h>

void printType64(t_64bits info, Elf64_Sym *actual) {
	// Ordre de check : U, u, A, B/b, D/d, C/c, G/g, I,
	// N, n, P, R/r, S/s, T/t, -, V/v, W/w, si rien ?

	char c = '?';

	if (actual->st_shndx == SHN_UNDEF)
		c = 'U';
	else if (ELF64_ST_BIND(actual->st_info) == STB_GNU_UNIQUE)
		c = 'u';
	else if (actual->st_shndx == SHN_ABS)
		c = 'A';
	else if (info.section[actual->st_shndx].sh_type == SHT_NOBITS &&
	         (info.section[actual->st_shndx].sh_flags &
	          (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE)) {
		c = 'B';
		if (ELF64_ST_BIND(actual->st_info) == STB_LOCAL)
			c = 'b';
	} else if (info.section[actual->st_shndx].sh_type == SHT_PROGBITS &&
	           (info.section[actual->st_shndx].sh_flags &
	            (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE)) {
		c = 'D';
		if (ELF64_ST_BIND(actual->st_info) == STB_LOCAL)
			c = 'd';
	} else if (ELF64_ST_TYPE(actual->st_info) == STT_COMMON &&
	           info.section[actual->st_shndx].sh_type == SHN_COMMON) {
		c = 'C';
		if (ELF64_ST_BIND(actual->st_info) == STB_LOCAL)
			c = 'c';
	}
	printf(" %c ", c);
}
int printInfo(t_nm *info) {

	if (info->is64Bits) {

		t_64bits info64 = info->infoBits.u_64bits;

		// Pointeur sur le premier element
		Elf64_Sym *sectionElements =
		    (Elf64_Sym *)((char *)info64.header + info64.symtab->sh_offset);

		// Boucle pour passer chaque symbole
		for (int i = 0;
		     i < (int)(info64.symtab->sh_size / info64.symtab->sh_entsize);
		     i++) {

			Elf64_Sym *actual = &sectionElements[i];
			//printf("Index name = %u, info = %c, value = %lu\n", actual->st_name,
			//       actual->st_info, actual->st_value);

			char *name = (char *)info64.header + info64.strtab->sh_offset +
			             actual->st_name;
			//			printf("Name = %s\n", name);
			if (!actual->st_value)
				printf("                ");
			else
				printf("%016lu", actual->st_value);
			printType64(info64, actual);
			printf("%s\n", name);
		}
	}

	return (1);
}
