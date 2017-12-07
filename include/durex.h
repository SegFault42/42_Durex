#ifndef DUREX_H
#define DUREX_H

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/file.h>
#include <stdbool.h>

#define	MAX_CLIENT	3
#define	BUFFSIZE	4096

typedef struct			s_connexion
{
	int					master_socket;
	int					opt;
	int					addrlen;
	struct sockaddr_in	address;
	int					client_socket[3];
}						t_connexion;

typedef struct			s_users
{
	int					new_socket;
	int					activity;
	int					i;
	int					sd;
	int					max_sd;
	int					nb_user;
	fd_set				readfds;
	int					key[3];
	char				pad[4];
}						t_users;

void	create_daemon(void);
bool	setup_deamon(t_connexion *connexion);
bool	run_daemon(t_connexion *connexion, char **envp);

char	*ft_decrypt(char *str);
char	*ft_crypt(char *str);

#endif
