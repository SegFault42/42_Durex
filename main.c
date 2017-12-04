#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	int	fd = 0;
	char	buff[4096] = "#include <stdio.h>\nint main()\n{\nputs(\"Hello World\");\n}";
	char	*arg[] = {"/usr/bin/gcc", "./test.c", "-o", "Durex", NULL};

	puts("rabougue");
	fd = open("test.c", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		return (errno);
	}
	write(fd, &buff, strlen(buff));
	if (execve("/usr/bin/gcc", arg, envp) == -1)
	{
		perror("gcc");
		return (errno);
	}
	
}
