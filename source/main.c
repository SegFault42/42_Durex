#include "durex.h"

int	main(int argc, char **argv, char **envp)
{
	t_connexion	connexion;
	memset(&connexion, 0, sizeof(connexion));

	create_daemon();
	if (setup_deamon(&connexion) == false)
		return (false);
	if (run_daemon(&connexion, envp) == false)
		return (false);
	return (0);
}
