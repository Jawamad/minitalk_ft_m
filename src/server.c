/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:48:10 by flmuller          #+#    #+#             */
/*   Updated: 2024/05/17 10:16:19 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

char	*complt_msg(char current_char, char *msg, siginfo_t *info)
{
	int		i;
	int		len;
	char	*msg_complt;

	len = ft_strlen(msg);
	msg_complt = ft_calloc(len + 2, sizeof(char));
	ft_memcpy(msg_complt, msg, len);
	free(msg);
	i = 0;
	while (msg_complt[i])
		i++;
	msg_complt[i++] = current_char;
	msg_complt[i] = '\0';
	kill(info->si_pid, SIGUSR2);
	return (msg_complt);
}

void	print_msg(siginfo_t *info, char **str)
{
	ft_putstr("message de ");
	ft_putnbr_fd(info->si_pid, 1);
	ft_putstr(" : ");
	ft_putstr(*str);
	ft_putstr("\n");
	kill(info->si_pid, SIGUSR1);
	free(*str);
	*str = NULL;
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static char	*str;
	static char	c;
	static int	i;

	(void) context;
	if (!str)
		str = ft_calloc(1, 1);
	if (signal == SIGUSR2)
		c |= (1 << i);
	if (i < 7)
	{
		i++;
		kill(info->si_pid, SIGUSR2);
	}
	else
	{
		if (c == '\0')
			print_msg(info, &str);
		else
			str = complt_msg(c, str, info);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	ft_memset(&s_sigaction, 0, sizeof(struct sigaction));
	s_sigaction.sa_sigaction = handle_signal;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
	{
		pause();
	}
	return (0);
}
