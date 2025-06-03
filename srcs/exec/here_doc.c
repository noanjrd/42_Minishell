/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:27 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 18:20:23 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_sigitn(int sig)
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

// int	ft_check_if_here_doc_after(t_token *token)
// {
// 	t_token *cpy_token;

// 	cpy_token = token;
// 	cpy_token = cpy_token->next;
// 	while (cpy_token && cpy_token->type != PIPE)
// 	{
// 		cpy_token = cpy_token->next ;
// 	}
// 	while (cpy_token)
// 	{
// 		if (cpy_token->type == HERE_DOC)
// 			return (1);
// 		cpy_token = cpy_token->next ;
// 	}
// 	return  (0);
// }

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
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			break ;
		}
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
	}
}

void	here_doc(t_token *token, t_data *data)
{
	int	fd;

	signal(SIGINT, ft_sigitn);
	signal(SIGQUIT, SIG_IGN);
	here_doc_start(token->next->value, data, 0, &fd);
	close(fd);
	fd = open("temp", O_RDONLY, 0700);
	data->fd_here_doc = fd;
	return ;
}
