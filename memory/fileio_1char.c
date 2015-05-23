// demonstrates using file operations to do what mmap did in mmap_demo.c
//
// reads and writes one character at a time

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int			fd;
	char		ch;

	fd = open(argv[1], O_RDWR);
	while (read(fd, &ch, 1)) {
		switch (ch) {
			case 'a': case 'e': case 'i': case 'o': case 'u':
				ch = '^';
				break;
			case '\n':
				break;
			default:
				ch = ' ';
				break;
			}
		lseek(fd, -1, SEEK_CUR);
		write(fd, &ch, 1);
		}
	close(fd);

	return 0;
}
