/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:27 by njard             #+#    #+#             */
/*   Updated: 2025/06/04 12:07:15 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	ft_sigint_here_doc(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		close(0);
// 		g_exit_code_signal = -99;
// 	}
// 	return ;
// }

static void	ft_write_in_fd(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static void	ft_printf_error(char *stop)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(stop, 2);
	ft_putstr_fd("')\n", 2);
	return ;
}

void	here_doc_start(char *stop, t_data *data, int tmp, int *fd)
{
	char	*line;

	tmp = dup(0);
	if (data->fd_here_doc > 0)
		close(data->fd_here_doc);
	unlink("temp");
	*fd = open("temp", O_RDWR | O_CREAT, 0700);
	while (1)
	{
		line = readline("> ");
		if (!line && g_exit_code_signal == -99)
		{
			dup2(tmp, 0);
			break ;
		}
		if (!line)
			return (ft_printf_error(stop));
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			break ;
		}
		ft_write_in_fd(*fd, line);
		free(line);
	}
}

void	here_doc(t_token *token, t_data *data)
{
	int	fd;

	signal(SIGINT, ft_sigint_here_doc);
	signal(SIGQUIT, SIG_IGN);
	here_doc_start(token->next->value, data, 0, &fd);
	close(fd);
	fd = open("temp", O_RDONLY, 0700);
	data->fd_here_doc = fd;
	return ;
}
