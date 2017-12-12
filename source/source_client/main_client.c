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
	ssize_t		ret_read = 0, ret_recv = 0;
	uint16_t	port;
	size_t		size = 0;

	port = is_port_valid(argv);
	sock = create_client((char *)"localhost", port);

	if (sock == -1)
	{
		perror("sock");
		return (false);
	}
	while (1)
	{
		ret_recv = recv(sock, buff, 4096, 0);
		write(1, &buff, ret_recv);
		if ((ret_read = read(0, buff, BUFFSIZE)) == -1)
		{
			perror("read");
			return (errno);
		}
		buff[ret_read -1] = '\0';
		if (!strcmp(buff, "quit"))
			return (0);
		else if (send(sock, buff, ret_read, 0) == -1)
		{
			perror("send");
			return (errno);
		}
		if (!strcmp(buff, "screen"))
		{
			memset(buff, 0, BUFFSIZE);
			int fd = open("./screen.png", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if ((ret_recv = recv(sock, buff, BUFFSIZE, 0)) == -1)
			{
				perror("send");
				return (errno);
			}
			printf("rcv = %s\n", buff);
			memset(buff, 0, BUFFSIZE);
			if ((ret_recv = recv(sock, buff, BUFFSIZE, 0)) == -1)
			{
				perror("send");
				return (errno);
			}
			printf("rcv = %s\n", buff);
			size = (size_t)atoi(buff);
			printf("size = %zu\n", size);
			memset(buff, 0, BUFFSIZE);

			char	*img = (char *)malloc(sizeof(char) * size);
			while (size > 0)
			{
				memset(img, 0, sizeof(char) * size);
				ret_recv = recv(sock, img, size, 0);
				printf("ret_recv = %zu\n", ret_recv);
				write(fd, img, ret_recv);
				size -= ret_recv;
				printf("size = %zu\n", size);
			}
			return(0);
		}
		memset(buff, 0, BUFFSIZE);
	}
}
