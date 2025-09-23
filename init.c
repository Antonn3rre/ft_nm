#include "ft_nm.h"
#include <elf.h>

// Get the file stat to check if it's not empty
// Project the file and store the pointer in info
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
	info->fileSize = fileStat.st_size;
	// TODO: check file type

	// Project file content
	info->mapped = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (info->mapped == MAP_FAILED) {
		perror("mmap");
		return (0);
	}
	return (1);
}

// Stores the project header after verifying if it exists
// Check if the ELF header info are logical
static int getProgramHeader(t_nm *info) {

	if (info->is64Bits) {

		Elf64_Ehdr *header = info->infoBits.u_64bits.header;
		if (header->e_phoff == 0) {
			info->infoBits.u_64bits.program = NULL;
			info->hasProgram = 0;
			return (1);
		}
		// Check erreur taille
		if (header->e_phentsize * header->e_phnum + header->e_phoff >
		    info->fileSize) {
			printf("error size program header\n");
			return (0);
		}
		info->infoBits.u_64bits.program =
		    (Elf64_Phdr *)(info->mapped + header->e_phoff);

	} else {

		Elf32_Ehdr *header = info->infoBits.u_32bits.header;
		if (header->e_phoff == 0) {
			info->infoBits.u_32bits.program = NULL;
			info->hasProgram = 0;
			return (1);
		}
		// Check erreur taille
		if (header->e_phentsize * header->e_phnum + header->e_phoff >
		    info->fileSize) {
			printf("error size program header\n");
			return (0);
		}
		info->infoBits.u_32bits.program =
		    (Elf32_Phdr *)(info->mapped + header->e_phoff);
	}
	info->hasProgram = 1;
	return (1);
}

// Stores the section header after verifying if it exists
// Check if the ELF header info are logical
static int getSectionHeader(t_nm *info) {

	if (info->is64Bits) {

		Elf64_Ehdr *header = info->infoBits.u_64bits.header;
		if (header->e_shoff == 0) {
			info->infoBits.u_64bits.section = NULL;
			info->hasSection = 0;
			return (1);
		}
		// Check erreur taille
		if (header->e_shentsize * header->e_shnum + header->e_shoff >
		    info->fileSize) {
			printf("error size section header\n");
			return (0);
		}
		info->infoBits.u_64bits.section =
		    (Elf64_Shdr *)(info->mapped + header->e_shoff);

	} else {

		Elf32_Ehdr *header = info->infoBits.u_32bits.header;
		if (header->e_shoff == 0) {
			info->infoBits.u_32bits.section = NULL;
			info->hasSection = 0;
			return (1);
		}
		// Check erreur taille
		if (header->e_shentsize * header->e_shnum + header->e_shoff >
		    info->fileSize) {
			printf("error size section header\n");
			return (0);
		}
		info->infoBits.u_32bits.section =
		    (Elf32_Shdr *)(info->mapped + header->e_shoff);
	}
	info->hasSection = 1;
	return (1);
}

// Check wether the file is in 32 or 64 bits
// Then stores then stores the ELF header in the right variable
static int getElfHeader(t_nm *info) {

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

	// Store ELF file in structured variables
	if (!getElfHeader(info) || !getProgramHeader(info) ||
	    !getSectionHeader(info))
		return (0);
	return (1);
}
