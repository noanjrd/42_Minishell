/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:27 by njard             #+#    #+#             */
/*   Updated: 2025/05/29 15:15:33 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_stop(char *instru)
{
	char *stop;
	int i;
	int j;

	i = 0;
	j = 0;
	while (instru[i] != '<')
		i++;
	i += 3;
	while (instru[i + j])
	{
		j++;
	}
	stop = malloc((j + 1) * sizeof(char));
	if (!stop)
		return (NULL);
	j = 0;
	while (instru[j + i])
	{
		stop[j] = instru[j + i];
		j++;
	}
	stop[j] = 0;
	return (stop);
}

static void	ft_sigitn(int sig)
{
	if (sig == SIGINT)
	{
		write(1,"\n",1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
		exit_code_signal = -99;
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

void	here_doc_start(char *stop, t_data *data, int tmp)
{
	char *line;
	int fd;

	tmp = dup(0);
	if (data->fd_here_doc > 0)
		close(data->fd_here_doc);
	unlink("temp");
	fd = open("temp", O_RDWR | O_CREAT, 0700);
	while (1)
	{
		line = readline("> ");
		if (!line && exit_code_signal == -99)
		{
			dup2(tmp, 0);
			break;
		}
		if (ft_strcmp(line,stop) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open("temp", O_RDONLY, 0700);
	data->fd_here_doc = fd;
}

void	here_doc(t_token *token, t_data *data)
{
	signal(SIGINT ,ft_sigitn);
	here_doc_start(token->next->value, data, 0);
	return ;
}
