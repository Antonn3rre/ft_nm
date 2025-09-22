#include "stdio.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

  int fd;

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
	char *file = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file == MAP_FAILED) {
    perror("mmap");
		return (0);
	}
	close(fd);

	printf("File = %s\n", file);

	return (0);
}
