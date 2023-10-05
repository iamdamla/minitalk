/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:12:19 by derblang          #+#    #+#             */
/*   Updated: 2023/05/12 09:39:17 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_message(int sig, siginfo_t *sig_info, void *context)
{
	static char	c;
	static int	i;

	if (sig == SIGUSR1)
		c += (1 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			kill(sig_info->si_pid, SIGUSR1);
		ft_putchar_fd(c, 1);
		c = 0;
		i = 0;
	}
	context = 0;
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &receive_message;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
