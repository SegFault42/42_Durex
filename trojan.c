#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	int	fd = 0;
	char	buff[4096] = {0};
	char	*arg[] = {"/usr/bin/gcc", "./test.c", "-o", "/bin/Durex", NULL};

	puts("rabougue\nkbensado");
	fd = open("./test.c", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		return (errno);
	}
	strcpy(buff, "#include <stdio.h>\nint main()\n{\nputs(\"Hello World\");\nwhile(42){}\n}");
	write(fd, &buff, strlen(buff));
	close(fd);
	if (execve("/usr/bin/gcc", arg, envp) == -1)
	{
		perror("gcc");
		return (errno);
	}
}
