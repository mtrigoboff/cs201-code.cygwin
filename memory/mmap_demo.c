// demonstrates mapping a file into memory

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int			fd;
	struct stat	fileInfo;
	int			fileSize;
	char*		mapAddr;
	char*		chPtr;
	int			i;

	fd = open(argv[1], O_RDWR);
	fstat(fd, &fileInfo);			// get information about file
	fileSize = fileInfo.st_size;
    mapAddr = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	for (i = 0, chPtr = mapAddr; i < fileSize - 1; i++, chPtr++)
		switch (*chPtr) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				*chPtr = '^';
				break;
			default:
				*chPtr = ' ';
				break;
			}
	munmap(mapAddr, fileSize);
	close(fd);
	return 0;
}
