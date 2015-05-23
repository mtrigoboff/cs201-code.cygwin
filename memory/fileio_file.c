// demonstrates using file operations to do what mmap did in mmap_demo.c
//
// reads entire file into memory

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int			fd;
	struct stat	fileInfo;
	int			fileSize;
	char*		chars;
	char*		chPtr;
	int			i;

	fd = open(argv[1], O_RDWR);
	fstat(fd, &fileInfo);			// get information about file
	fileSize = fileInfo.st_size;
	chars = malloc(fileSize);
	read(fd, chars, fileSize);
	for (i = 0, chPtr = chars; i < fileSize - 1; i++, chPtr++)
		switch (*chPtr) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				*chPtr = '^';
				break;
			default:
				*chPtr = ' ';
				break;
			}
	lseek(fd, 0, SEEK_SET);
	write(fd, chars, fileSize);
	free(chars);
	close(fd);

	return 0;
}
