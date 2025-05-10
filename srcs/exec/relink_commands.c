/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:56:37 by njard             #+#    #+#             */
/*   Updated: 2025/05/10 17:53:50 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **ft_join_tab(char **tab, char *value, char *value_app)
{
	int i;
	int j;
	int z;
	char **new_tab = NULL;

	i = 0;
	j = 0;
	// printf("&& %s, %s\n", value, value_app);
	while (tab && tab[i])
		i++;
	if (value)
		i++;
	new_tab = malloc((i + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (tab && tab[j])
	{
		// printf("derrr\n");
		while (tab[j][i])
			i++;
		new_tab[j] = malloc((i + 1) * sizeof(char));
		i = 0;
		while (tab[j][i])
		{
			new_tab[j][i] = tab[j][i];
			i++;
		}
		new_tab[j][i] = 0;
		j++;
	}
	i = 0;
	if (tab == NULL && value)
	{
		// printf("popo\n");
		while (value[i])
			i++;
		new_tab[j] = malloc((i + 1) * sizeof(char));
		i = 0;
		while(value[i])
		{
			new_tab[j][i] = value[i];
			i++;
		}
		new_tab[j][i] = 0;
		j++;
	}
	i = 0;
	while (value_app[i])
			i++;
	new_tab[j] = malloc((i + 1) * sizeof(char));
	i = 0;
	while (value_app[i])
	{
		new_tab[j][i] = value_app[i];
		i++;
	}
	new_tab[j][i] = 0;
	j++;
	new_tab[j] = NULL;
	// i = 0;
	// printf("---");
	// while (new_tab[i])
	// {
	// 	printf("%s ", new_tab[i]);
	// 	i++;
	// }
	// printf("\n");
	return (new_tab);
}

char *ft_join_free(char *s1, char *s2)
{
	int i;
	int j;
	char *new_string;

	i = 0;
	j = 0;
	while(s1[i])
		i++;
	while(s2[j])
		j++;
	new_string = malloc((i + j + 2) * sizeof(char));
	if (!new_string)
		return(NULL);
	i = 0;
	j = 0;
	while(s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	new_string[i] = ' ';
	i++;
	while (s2[j])
		new_string[i++] = s2[j++];
	new_string[i] = 0;
	free(s1);
	// free(s2);
	return(new_string);
}

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	cmd->index = cpy_cmd->index;
	cmd->red_append = cpy_cmd->red_append;
	cmd->fdout = cpy_cmd->fdout;
	cmd->outfile = ft_copy(cpy_cmd->outfile);
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	temp = cpy_cmd->next;
	free(cpy_cmd->infile);
	free(cpy_cmd->value);
	free(cpy_cmd->tab);
	free(cpy_cmd->outfile);
	free(cpy_cmd);
	cmd->next = temp;
	// printf("|%s\n", cmd->value);
	// if (cmd->next)
	// 	printf("|%s\n", cmd->next->value);
	return ;
}

void	relink_commands(t_token *token, t_cmd *cmd)
{
	// t_cmd *cpy_cmd;
	int i;
	int z = 0;

	i = 0;
	// cpy_cmd = cmd->next;
	while (token)
	{
		// if (cmd->next)
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		// else
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
		if (token->next && token->next->type != PIPE && cmd->next && cmd->type != IN_OUT_FILENAME)
		{
			if (cmd->next && cmd->next->type == IN_OUT_FILENAME)
			{
				// printf("bababa\n");
				// if (z == 0)
				if (cmd->tab == NULL)
					cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
				// cmd = cmd->next;
				// token  =token->next;
				z = 1;
			}
			else
			{
				// printf("lol\n");
				put_tab(cmd, cmd->next);
				z = 1;
			}
			// if (cmd->next && token->next && (token->next->type == REDIRECT_OUT || token->next->type == PIPE) )
			// 	cmd = cmd->next;
		}
		else if (cmd->tab == NULL)
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		// else

		// printf("next %s\n", cmd->value);
		if (token->next && token->next->type == PIPE)
		{
			z = 0;
			// printf("idkkk %s\n", cmd->value);
			cmd = cmd->next;
			token = token->next;
			token = token->next;
			continue;
		}
		if (token && cmd->next && ft_strcmp(token->value, cmd->value) == 0)
		{
			// z = 0;
			cmd = cmd->next;
			// printf("nddd %s\n", cmd->value);
			// token = token->next;
		}
		i++;
		token = token->next;
	}
	return ;
}
