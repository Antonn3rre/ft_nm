#include "ft_nm.h"

int main(int argc, char **argv) {

	t_nm info;

	if (argc > 2)
		return (0);

	if (!init(argc, argv, &info))
		return (0);
	printf("e_phoff = %u, e_phentsize = %u, e_phnum = %u\n",
	       (unsigned int)info.infoBits.u_64bits.header->e_phoff,
	       (unsigned int)info.infoBits.u_64bits.header->e_phentsize,
	       (unsigned int)info.infoBits.u_64bits.header->e_phnum);
	printf("e_shoff = %u, e_shentsize = %u, e_shnum = %u\n",
	       (unsigned int)info.infoBits.u_64bits.header->e_shoff,
	       (unsigned int)info.infoBits.u_64bits.header->e_shentsize,
	       (unsigned int)info.infoBits.u_64bits.header->e_shnum);
	//	printf("File = %s\n", file);
	if (info.hasProgram)
		printf("Struct phdr, type = %u\n",
		       info.infoBits.u_64bits.program->p_type);
	else
		printf("No program header\n");
	if (info.hasSection)
		printf("Struct shdr, type = %u\n",
		       info.infoBits.u_64bits.section->sh_type);
	else
		printf("No section header\n");

	// Get the .symtab header section
	if (!findSymtabHeader(&info))
		return (0);
	return (0);
}
