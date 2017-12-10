#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

static void	usage()
{
	puts("Usage : ./fusion Durex file_to_fusion");
	exit(-1);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		usage();

	int	fd_1 = 0, fd_2 = 0;
	off_t	locat;

	if ( (fd_1 = open(argv[1], O_RDWR | O_APPEND)) == -1)
	{
		perror("open");
		return (errno);
	}
	if ( (fd_2 = open(argv[2], O_RDONLY)) == -1)
	{
		perror("open");
		return (errno);
	}
	locat = lseek(fd_1, 0, SEEK_END);
	if (locat == -1)
	{
		perror("lseek");
		return (errno);
	}
	dprintf(fd_1, "Salut");
}
