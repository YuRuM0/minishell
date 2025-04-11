/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flima <flima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:16:27 by flima             #+#    #+#             */
/*   Updated: 2025/04/11 20:31:38 by flima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interative_signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal_main_loop()
{
	if (g_last_signal)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	g_last_signal = 0;
	setup_signal_handlers(INTERACTIVE);
}

void	setup_signal_handlers(t_signal_mode	mode)
{
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;

	ft_memset(&act_sigint, 0, sizeof(struct sigaction));
	ft_memset(&act_sigquit, 0, sizeof(struct sigaction));
	sigemptyset(&act_sigint.sa_mask);
	sigemptyset(&act_sigquit.sa_mask);
	sigaddset(&act_sigint.sa_mask, SIGINT);
	act_sigquit.sa_handler = SIG_IGN;
	if (mode == INTERACTIVE)
		act_sigint.sa_handler = interative_signal_handler;
	if (mode == NON_INTERACTIVE)
		act_sigint.sa_handler = SIG_IGN;
	else if (mode == HEREDOC_CHILD)
		act_sigint.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act_sigint, NULL);
	sigaction(SIGQUIT, &act_sigquit, NULL);
}


