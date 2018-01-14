#ifndef DUREX_H
#define DUREX_H

#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/file.h>
#include <stdbool.h>
#include <wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#define	MAX_CLIENT	3
#define	BUFFSIZE	4096
#define OLD			term[0]
#define NEW			term[1]
#define CAM			1
#define SCREEN		2

# define BLACK	"\033[30m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define PURPLE	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"
# define ORANGE	"\033[38;5;208m"
# define PINK	"\033[38;5;13m"
# define GREY	"\033[38;5;246m"

# define END	"\033[0m"

# define PSWD	"K<JK"

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
bool	setup_deamon(t_connexion *connexion, uint16_t port);
bool	run_daemon(t_connexion *connexion, char **envp);

char	*ft_decrypt(char *str);
char	*ft_crypt(char *str, off_t size);


int			create_client(char *addr, uint16_t port);
uint16_t	is_port_valid(char **argv);
int			usage(char *argv);

#endif
