#include "ft_nm.h"

static int getFileInfo(int fd, t_nm *info) {
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
	info->mapped = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (info->mapped == MAP_FAILED) {
		perror("mmap");
		return (0);
	}
	return (1);
}

int init(int argc, char **argv, t_nm *info) {

	int fd;

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
	if (!getFileInfo(fd, info))
		return (close(fd), 0);
	close(fd);

	// Check if the file is in 32 bits or 64 bits
	unsigned char *data = (unsigned char *)info->mapped;

	if (data[EI_CLASS] == ELFCLASS32) {
		info->infoBits.u_32bits.header = (Elf32_Ehdr *)info->mapped;
		info->is64Bits = 0;
		printf("ELF 32 bits\n");
	} else if (data[EI_CLASS] == ELFCLASS64) {
		info->infoBits.u_64bits.header = (Elf64_Ehdr *)info->mapped;
		info->is64Bits = 1;
		printf("ELF 64 bits\n");
	} else {
		printf("Format ELF inconnu\n");
	}
	return (1);
}
