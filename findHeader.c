#include "ft_nm.h"
#include <elf.h>
#include <sys/uio.h>

int ft_strncmp(const char *s1, const char *s2, size_t n) {
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n) {
		if ((unsigned char)s1[i] != (unsigned char)s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int findSymtabHeader(t_nm *info) {

	if (info->is64Bits) {

		info->infoBits.u_64bits.strtab = NULL;
		info->infoBits.u_64bits.symtab = NULL;

		t_64bits info64 = info->infoBits.u_64bits;

		// Pointeur sur le premier section header
		Elf64_Shdr *sectionHeaders =
		    (Elf64_Shdr *)((char *)info64.header + info64.header->e_shoff);

		// On recupere la section string table
		Elf64_Shdr *stringTable = &sectionHeaders[info64.header->e_shstrndx];

		printf("Nombre de sections: %d, Taille d'une entree: %d\n",
		       info64.header->e_shnum, info64.header->e_shentsize);

		for (int i = 0; i < info64.header->e_shnum; i++) {

			Elf64_Shdr *actual = &sectionHeaders[i];

			//printf("Section %d: name index = %u, type = %u\n", i,
			//       actual->sh_name, actual->sh_type);

			char *name = (char *)info64.header + stringTable->sh_offset +
			             actual->sh_name;
			//printf("Name = %s\n", name);

			if (!ft_strncmp(name, ".symtab", 8)) {
				info->infoBits.u_64bits.symtab = actual;
			} else if (!ft_strncmp(name, ".strtab", 8)) {
				info->infoBits.u_64bits.strtab = actual;
			}
		}

		if (!info->infoBits.u_64bits.strtab || !info->infoBits.u_64bits.symtab)
			return (0); // TODO: check leak
	}
	// TODO: meme chose pour 32bits
	return (1);
}
