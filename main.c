#include "ft_nm.h"

int main(int argc, char **argv) {

	t_nm info;

	if (argc > 2)
		return (0);

	if (!init(argc, argv, &info))
		return (0);
	/*
	printf("e_phoff = %u\ne_phentsize = %u\n, e_phnum = %u\n",
	       (unsigned int)info.infoBits.u_64bits.header->e_phoff,
	       (unsigned int)info.infoBits.u_64bits.header->e_phentsize,
	       (unsigned int)info.infoBits.u_64bits.header->e_phnum);
	printf("e_shoff = %u\ne_shentsize = %u\n, e_shnum = %u\n",
	       (unsigned int)info.infoBits.u_64bits.header->e_shoff,
	       (unsigned int)info.infoBits.u_64bits.header->e_shentsize,
	       (unsigned int)info.infoBits.u_64bits.header->e_shnum);
*/
	//	printf("File = %s\n", file);

	return (0);
}
