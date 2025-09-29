#include "ft_nm.h"
#include <elf.h>

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
			printf("Index name = %u, info = %c, value = %lu\n", actual->st_name,
			       actual->st_info, actual->st_value);
			if (actual->st_info == STT_OBJECT)
				printf("object\n");
			else if (actual->st_info == STT_FUNC)
				printf("function\n");

			char *name = (char *)info64.header + info64.strtab->sh_offset +
			             actual->st_name;
			//			printf("Name = %s\n", name);

			printf("%016lu %c %s\n", actual->st_value, actual->st_info, name);
		}
	}

	return (1);
}
