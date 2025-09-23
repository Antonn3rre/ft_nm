#include "ft_nm.h"

int main(int argc, char **argv) {

	int fd;
	t_nm info;

	if (argc > 2)
		return (0);

	// Open file
	if (argc == 2) {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			perror("nm"); // TODO: print file name
			return (0);
		}
	} else {
		fd = open("a.out", O_RDONLY);
		if (fd == -1) {
			perror("nm: 'a.out'");
			return (0);
		}
	}

	// Get file info
	struct stat fileStat;
	if (fstat(fd, &fileStat) == -1) {
		perror("fstat");
		return (0);
	}
	printf("uid = %d, size = %ld\n", fileStat.st_uid, fileStat.st_size);
	if (fileStat.st_size == 0) {
		printf("Empty file\n");
		return (0);
	}
	// TODO: check file type

	// Project file content
	info.mapped = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (info.mapped == MAP_FAILED) {
		perror("mmap");
		return (0);
	}
	close(fd);

	// Check if the file is in 32 bits or 64 bits
	unsigned char *data = (unsigned char *)info.mapped;

	if (data[EI_CLASS] == ELFCLASS32) {
		info.infoBits.u_32bits.header = (Elf32_Ehdr *)info.mapped;
		info.is64Bits = 0;
		printf("ELF 32 bits\n");
	} else if (data[EI_CLASS] == ELFCLASS64) {
		info.infoBits.u_64bits.header = (Elf64_Ehdr *)info.mapped;
		info.is64Bits = 1;
		printf("ELF 64 bits\n");
	} else {
		printf("Format ELF inconnu\n");
	}

	//	printf("File = %s\n", file);

	return (0);
}
