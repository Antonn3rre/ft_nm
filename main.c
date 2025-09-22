#include "stdio.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if (argc != 2) // a changer pourt a.out par defaut
		return (0);

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		printf("Error opening file\n");
		return (0);
	}
	struct stat fileStat;
	if (fstat(fd, &fileStat) == -1) {
		printf("fstat error\n");
		return (0);
	}
	printf("uid = %d, size = %ld\n", fileStat.st_uid, fileStat.st_size);
	if (fileStat.st_size == 0) {
		printf("Empty file\n");
		return (0);
	}

	char *file = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
		printf("mmap fail\n");
		return (0);
	}
	close(fd);

	printf("FIle = %s\n", file);

	return (0);
}
