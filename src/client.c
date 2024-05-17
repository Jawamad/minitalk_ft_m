/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:21:39 by flmuller          #+#    #+#             */
/*   Updated: 2024/05/17 10:19:51 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

char	*g_str;

void	send_end_str(int pid_server, char end)
{
	static int	cursor_end;

	if (cursor_end <= 7)
	{
		if ((end >> cursor_end) & 1)
			kill(pid_server, SIGUSR2);
		else
			kill(pid_server, SIGUSR1);
		cursor_end++;
	}
	if (cursor_end == 8)
		cursor_end = 0;
}

void	send_bit(int pid)
{
	static unsigned int	i;
	static unsigned int	cpt_char;

	if (i < ft_strlen(g_str))
	{
		if (cpt_char <= 7)
		{
			if ((g_str[i] >> cpt_char) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			cpt_char++;
		}
		if (cpt_char == 8)
		{
			i++;
			cpt_char = 0;
		}
	}
	else
		send_end_str(pid, '\0');
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_putstr("Message received 👍\n");
		exit(1);
	}
	if (signal == SIGUSR2)
	{
		send_bit(info->si_pid);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sigaction;

	if (argc != 3)
	{
		ft_putstr("Error, the programm need 2 parameters. PID and Message\n");
		exit(1);
	}
	g_str = argv[2];
	send_bit(ft_atoi(argv[1]));
	ft_memset(&s_sigaction, 0, sizeof(struct sigaction));
	s_sigaction.sa_sigaction = handle_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
