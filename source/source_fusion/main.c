#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdbool.h>

static void	usage()
{
	puts("Usage : ./fusion Durex file_to_fusion");
}

static char	*ft_crypt(char *buff, off_t size)
{
	off_t	i = 0;

	while (i < size)
	{
		buff[i] += 42;
		++i;
	}
	return (buff);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		usage();
		return (-1);
	}

	int			fd_1 = 0, fd_2 = 0;
	off_t		locat;
	struct stat	st;

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
	fstat(fd_2, &st);
	char	buff_1[st.st_size];
	read(fd_2, buff_1, (size_t)st.st_size);
	ft_crypt(buff_1, st.st_size);
	write(fd_1, &buff_1, (size_t)st.st_size);
	write(fd_1, &locat, sizeof(locat));
	close(fd_1);
	close(fd_2);
	puts("Fusion success");
}
