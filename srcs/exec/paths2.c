/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:07:55 by njard             #+#    #+#             */
/*   Updated: 2025/06/03 18:22:22 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_exact_command_from_path(char *value)
{
	char	*new_value;
	int		i;
	int		j;
	int		z;

	z = 0;
	i = 0;
	j = 0;
	while (value[j])
		j++;
	while (value[i] && value[i] != ' ')
		i++;
	if (value[i - 1])
		i--;
	while (value[i] && value[i] != '/')
		i--;
	i++;
	new_value = malloc((j - i + 1) * sizeof(char));
	if (!new_value)
		return (NULL);
	while (value[i] && value[i] != ' ')
		new_value[z++] = value[i++];
	new_value[z] = 0;
	return (new_value);
}

char	*extract_command_from_path(char *value)
{
	char	*new_value;
	int		i;
	int		j;
	int		z;

	z = 0;
	i = 0;
	j = 0;
	while (value[j])
		j++;
	while (value[i] && value[i] != ' ')
		i++;
	while (value[i] != '/')
		i--;
	i++;
	new_value = malloc((j - i + 1) * sizeof(char));
	if (!new_value)
		return (NULL);
	while (value[i])
		new_value[z++] = value[i++];
	new_value[z] = 0;
	free(value);
	return (new_value);
}

void	ft_change_token(t_cmd *cmd, t_token *token)
{
	t_token *cpy_t;

	cpy_t = token;
	while (cpy_t->index != cmd->index)
	{
		cpy_t = cpy_t->next;
	}
	free(cpy_t->value);
	cpy_t->value = ft_copy(cmd->tab[0]);
}

void	ft_check_if_value_path(t_cmd *cmd, t_token *token)
{
	struct stat	sb;

	if (!cmd->path)
	{
		if (access(cmd->tab[0], X_OK) == 0)
		{
			stat(cmd->tab[0], &sb);
			if (S_ISREG(sb.st_mode))
			{
				cmd->path = ft_copy(cmd->tab[0]);
				free(cmd->tab[0]);
				cmd->tab[0] = extract_exact_command_from_path(cmd->value);
				cmd->value = extract_command_from_path(cmd->value);
				ft_change_token(cmd, token);
			}
		}
	}
	return ;
}
