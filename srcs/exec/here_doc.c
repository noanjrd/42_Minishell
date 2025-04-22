/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:23:27 by njard             #+#    #+#             */
/*   Updated: 2025/04/21 11:12:25 by njard            ###   ########.fr       */
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

void	here_doc_start(char *stop, t_data *data)
{
	char *line;
	int fd;

	fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line,stop) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	data->fdin = fd;
	return ;
}

void	here_doc(char *instru, t_data *data)
{
	// char *stop;

	// stop = get_stop(instru);
	// printf("%s\n", stop);
	here_doc_start(instru, data);
	// free(stop);
	return ;
}

