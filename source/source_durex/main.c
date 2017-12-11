#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

static char	*ft_decrypt(char *buff, off_t size)
{
	off_t	i = 0;

	while (i < size)
	{
		buff[i] -= 42;
		++i;
	}
	return (buff);
}

int	main(int argc, char **argv)
{
	int	fd = 0;
	off_t	size_daemon = 0;
	struct stat	st;

	(void)argc;
	puts("rabougue\nkbensado");
	fd = open(argv[0], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(errno);
	}
	fstat(fd, &st);
	if (lseek(fd, (off_t)st.st_size - (off_t)sizeof(size_daemon), SEEK_SET) == -1)
	{
		perror("lseek");
		exit(errno);
	}
	if (read(fd, &size_daemon, sizeof(size_daemon)) < 1)
	{
		perror("read");
		exit(errno);
	}
	close(fd);

	fd = open(argv[0], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(errno);
	}
	lseek(fd, size_daemon, SEEK_SET);

	char	buff[st.st_size - size_daemon];
	memset(&buff, 0, sizeof(buff));

	read(fd, &buff, sizeof(buff));
	ft_decrypt(buff, (off_t)sizeof(buff));
	close(fd);
	remove("./Durex_copy");
	if ((fd = open("./Durex_copy", O_CREAT | O_RDWR, 0744)) == -1)
	{
		perror("open");
		return (errno);
	}
	write(fd, &buff, sizeof(buff));

	close(fd);
}
