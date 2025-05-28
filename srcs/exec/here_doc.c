/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:27 by njard             #+#    #+#             */
/*   Updated: 2025/05/28 16:06:31 by njard            ###   ########.fr       */
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

void	here_doc_start(char *stop, t_data *data)
{
	char *line;
	int fd;
	int	tmp;

	tmp = dup(0);
	fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0700);
	while (1)
	{
		line = readline("> ");
		if (!line && exit_code_signal == -99)
		{
			dup2(tmp, 0);
			// signal(SIGINT, &ft_sigitn);
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
	// printf("[DBG]\n");
	// exit_code_signal = 0;
	return ;
}

void	here_doc(t_token *token, t_data *data)
{
	signal(SIGINT ,ft_sigitn);
	here_doc_start(token->next->value, data);
	// free(stop);
	return ;
}
