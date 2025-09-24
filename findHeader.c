#include "ft_nm.h"
#include <elf.h>
#include <sys/uio.h>

int findSymtabHeader(t_nm *info) {

	if (info->is64Bits) {

		t_64bits info64 = info->infoBits.u_64bits;

		Elf64_Off totalSize =
		    info64.header->e_shentsize * info64.header->e_shnum;
		for (Elf64_Off i = info64.header->e_shoff; i < totalSize;
		     i += info64.header->e_shentsize) {

			Elf64_Shdr *actual = (Elf64_Shdr *)info64.header + i;
		}
	}
	return (1);
}
