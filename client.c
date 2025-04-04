/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:13:09 by hiipek            #+#    #+#             */
/*   Updated: 2025/03/02 13:54:46 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack_received;

void	ack_handler(int signo)
{
	(void)signo;
	g_ack_received = 1;
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

void	send_char(int server_pid, char c)
{
	struct sigaction	sa;
	int					i;

	i = 0;
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	while (i < 8)
	{
		g_ack_received = 0;
		if (c & (1 << i))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (g_ack_received == 0)
			pause();
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_id;

	i = 0;
	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			send_char(server_id, argv[2][i]);
			i++;
		}
	}
	else
		write(1, "The number of arguments must be three!", 39);
}
