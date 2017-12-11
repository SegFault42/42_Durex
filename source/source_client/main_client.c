#include "durex.h"

/*char	*ft_crypt(char *str)*/
/*{*/
	/*int	i;*/

	/*i = 0;*/
	/*if (str == NULL)*/
		/*return (NULL);*/
	/*while (str[i] != '\0')*/
		/*i++;*/
	/*i--;*/
	/*while (i >= 0)*/
	/*{*/
		/*str[i] += 5;*/
		/*i--;*/
	/*}*/
	/*return (str);*/
/*}*/

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
		if (!strcmp(buff, "screenshot"))
		{
			/*int fd = open("./screen.png", O_RDWR | O_CREAT | O_TRUNC, 0644);*/
			memset(&buff, 0, BUFFSIZE);
			while ((ret_recv = recv(sock, buff, BUFFSIZE, 0)) > 0)
			{
				if (!strcmp(buff, "finish"))
					break ;
				write(1, &buff, ret_recv);
				memset(&buff, 0, BUFFSIZE);
			}
		return(0);
		}
		memset(&buff, 0, BUFFSIZE);
	}
}
