/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 21:44:03 by rabougue          #+#    #+#             */
/*   Updated: 2017/11/24 05:15:54 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

static int	usage(char *argv)
{
	dprintf(2, "Usage : %s [addr] [port] (between 1024 and 65535)\n", argv);
	exit(EXIT_FAILURE);
}


uint16_t	is_port_valid(char **argv)
{
	uint64_t	port;

	if (argv[1][0] == '-' || (port = (uint64_t)atoi(argv[2])) < 1024 || port > 65535)
		return ((uint16_t)usage(argv[0]));
	return ((uint16_t)port);
}
