/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:07:27 by naankour          #+#    #+#             */
/*   Updated: 2025/06/04 12:07:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_main(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code_signal = 130;
	}
	return ;
}

void	ft_sig_main(void)
{
	signal(SIGINT, ft_sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigint_exec(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_code_signal = 130;
	}
	else
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_code_signal = 130;
	}
	return ;
}

void	ft_sigint_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
		g_exit_code_signal = -99;
	}
	return ;
}
