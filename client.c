/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:51:39 by derblang          #+#    #+#             */
/*   Updated: 2023/05/12 09:34:02 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i++;
	}
}

void	send_message(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
}

void	server_signal(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message recieved!\n");
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &server_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		ft_printf("Expected arguments: ./client [PID] [MESSAGE]");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		ft_printf("Opps, wrong PID\n");
	else
	{
		ft_printf("message sent!\n");
		send_message(pid, argv[2]);
	}
	return (0);
}
