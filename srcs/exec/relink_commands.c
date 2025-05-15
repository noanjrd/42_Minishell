/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:22:15 by njard             #+#    #+#             */
/*   Updated: 2025/05/15 14:41:47 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **allocate_new_tab(char **tab, char *value)
{
	int i = 0;
	char **new_tab;

	while (tab && tab[i])
		i++;
	if (value)
		i++;
		
	new_tab = malloc((i + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	return (new_tab);
}

int copy_existing_tab(char **new_tab, char **tab, int j)
{
	int i;

	while (tab && tab[j])
	{
		i = 0;
		while (tab[j][i])
			i++;
		new_tab[j] = malloc((i + 1) * sizeof(char));
		if (!new_tab[j])
			return (j);
		i = 0;
		while (tab[j][i])
		{
			new_tab[j][i] = tab[j][i];
			i++;
		}
		new_tab[j++][i] = 0;
	}
	return (j);
}

int copy_value(char **new_tab, char *value, int j)
{
	int i = 0;

	while (value[i])
		i++;
	new_tab[j] = malloc((i + 1) * sizeof(char));
	if (!new_tab[j])
		return (j);
		
	i = 0;
	while (value[i])
	{
		new_tab[j][i] = value[i];
		i++;
	}
	new_tab[j++][i] = 0;
	return (j);
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while(tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

char **ft_join_tab(char **tab, char *value, char *value_app)
{
	char **new_tab;
	int j = 0;
		
	new_tab = allocate_new_tab(tab, value);
	if (!new_tab)
		return (NULL);
		
	j = copy_existing_tab(new_tab, tab, j);
	if (!tab && value)
		j = copy_value(new_tab, value, j);
		
	j = copy_value(new_tab, value_app, j);
	new_tab[j] = NULL;
	ft_free_tab(tab);
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
	return(new_string);
}

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	// cmd->index = cpy_cmd->index;
	cmd->red_append = cpy_cmd->red_append;
	cmd->fdout = cpy_cmd->fdout;
	cmd->outfile = ft_copy(cpy_cmd->outfile);
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	if (cpy_cmd->infile)
		cmd->infile = ft_copy(cpy_cmd->infile);
	temp = cpy_cmd->next;
	free(cpy_cmd->infile);
	free(cpy_cmd->value);
	free(cpy_cmd->tab);
	free(cpy_cmd->fdpipe);
	free(cpy_cmd->outfile);
	free(cpy_cmd);
	cmd->next = temp;
	// printf("|%s\n", cmd->value);
	// if (cmd->next)
	// 	printf("|%s\n", cmd->next->value);
	return ;
}

void	relink_commands(t_token *token, t_cmd *cpy_cmd)
{
	// t_cmd *cpy_cmd;
	int i;
	t_cmd *cmd;
	int z = 0;

	i = 0;
	cmd = cpy_cmd;
	while (token)
	{
		if (cmd->next)
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		else
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
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
		printf("next %s\n", cmd->value);
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
	cmd = cpy_cmd;
	while (cmd)
	{
		if (cmd->tab == NULL) 
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		cmd = cmd->next;
	}
	return ;
}
