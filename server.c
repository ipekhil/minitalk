/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiipek <hiipek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:13:24 by hiipek            #+#    #+#             */
/*   Updated: 2025/03/02 13:55:06 by hiipek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signalnum, siginfo_t *info, void *context)
{
	static int	i;
	static char	c;

	(void)context;
	if (signalnum == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	ft_putpid(int pid)
{
	char	c;

	if (pid > 9)
		ft_putpid(pid / 10);
	c = pid % 10 + 48;
	write(1, &c, 1);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	write(1, "Server PID: \n", 13);
	ft_putpid(pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
