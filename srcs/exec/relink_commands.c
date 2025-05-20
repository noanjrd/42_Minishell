/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:22:15 by njard             #+#    #+#             */
/*   Updated: 2025/05/20 15:36:38 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void printf_cmd2(t_cmd *cmd)
{
	t_cmd *current = cmd;
	int i = 0;

	while (current)
	{
		i = 0;
		printf("val=%s, in=%s, out=%s, fdin=%d, fdout=%d, i=%d, here=%d, appd=%d, path=%s , deleted=%d ",
			current->value,
			current->infile ? current->infile : "NULL",
			current->outfile ? current->outfile : "NULL",
			current->fdin,
			current->fdout,
			current->index,
			current->here_doc,
			current->red_append,
		current->path,
	current->deleted);
		printf("tab = ");
		if (current->tab)
		{
			while (current->tab && current->tab[i])
			{
				printf("| %s", current->tab[i]);
				i++;
			}
		}
		printf("\n");
		current = current->next;
	}
	printf("--------------------------------------------\n");
	return ;
}

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	// if (cpy_cmd->value[0] == '$')
	// 	return ;
	temp = NULL;
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
	return ;
}

void	put_tab_recompose(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

	// if (cpy_cmd->value[0] == '$')
	// 	return ;
	temp = NULL;
	cmd->red_append = cpy_cmd->red_append;
	if (cpy_cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = ft_copy(cpy_cmd->outfile);
	}
	cmd->fdout = cpy_cmd->fdout;
	cmd->next->end = 1;
	// cmd->outfile = ft_copy(cpy_cmd->outfile);
	cmd->tab = ft_join_tab(cmd->tab, cmd->value, cpy_cmd->value);
	cmd->value = ft_join_free(cmd->value, cpy_cmd->value);
	free(cmd->infile);
	cmd->infile = NULL;
	cpy_cmd->deleted = 1;
	// if (cpy_cmd->infile)
	// 	cmd->infile = ft_copy(cpy_cmd->infile);
	// temp = cpy_cmd->next;
	// free(cpy_cmd->infile);
	// free(cpy_cmd->value);
	// free(cpy_cmd->tab);
	// free(cpy_cmd->fdpipe);
	// free(cpy_cmd->outfile);
	// free(cpy_cmd);
	// cmd->next = temp;
	return ;
}

t_cmd *find_cmd_index(t_token *token, t_cmd *cmd)
{
	t_cmd *cpy_cmd;

	cpy_cmd = cmd;
	while (cpy_cmd && cpy_cmd->index != token->index)
	{
		cpy_cmd = cpy_cmd->next;
	}
	return (cpy_cmd);
}

void ft_check_echo_plus(t_token *token, t_cmd *cmd)
{
	t_cmd *cpy_cmd;
	t_cmd *temp_cmd;
	t_token *cpy_token;
	t_token *temp;

	// printf("here\n");
	temp_cmd = NULL;
	cpy_cmd = cmd;
	cpy_token = token;
	while (cpy_token)
	{
		if (token->type == WORD)
		{
			temp = cpy_token;
			while (cpy_token && ft_check_type(cpy_token) == 0)
			{
				cpy_token = cpy_token->next;
				// printf("loop\n");
			}
			if (!cpy_token || !cpy_token->next || cpy_token->type == PIPE || !cpy_token->next->next)
			{
				if (cpy_token && cpy_token->next)
					cpy_token = cpy_token->next;
				continue ;
			}
			else
				cpy_token = cpy_token->next->next;
			while (cpy_token &&  ft_check_type(cpy_token) == 0)
			{
				// printf("token %s\n", cpy_token->value);
				temp_cmd = find_cmd_index(cpy_token, cmd);
				if (!temp_cmd)
				{
					// printf("ERROR: no matching cmd for token index %s\n", cpy_token->value);
					cpy_token = cpy_token->next;
					continue;
				}
				else
				{
					// printf("cmd %s\n", temp_cmd->value);
					// temp_cmd->deleted = 1;
					if (!find_cmd_index(temp, cmd))
					{
						cpy_token = cpy_token->next;
						continue ;
					}
					// printf("cmd ancient %s\n", find_cmd_index(temp, cmd)->value);
					put_tab_recompose(find_cmd_index(temp, cmd),find_cmd_index(cpy_token, cmd));
					temp->next = cpy_token;
					cpy_token = cpy_token->next;
				}
			}
			// printf("next2\n");
		}
		else
		{
			// printf("next\n");
			cpy_token = cpy_token->next;
		}
	}
	return ;
}

void	rest_tab(t_token *token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;

	cmd = cpy_cmd;
	while (cmd)
	{
		if (cmd->tab == NULL) 
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		cmd = cmd->next;
	}
	ft_check_echo_plus(token, cpy_cmd);
	// printf_cmd2(cpy_cmd);
	return ;
}

void	relink_commands(t_token *cpy_token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;
	t_token *token;

	token = cpy_token;
	cmd = cpy_cmd;
	if (ft_check_type(token) == 1)
	{
		token = token->next->next;
		cmd = cmd->next;
	}
	while (token)
	{
		// if (cmd->next)
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		// else
		// 	printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
		if (token->next && cmd && cmd->next && token->type != REDIRECT_OUT && token->type != REDIRECT_APPEND &&token->type != HERE_DOC  &&  token->type != PIPE && token->type != REDIRECT_IN && cmd->next && cmd->type != IN_OUT_FILENAME && ft_check_type(token->next) == 0)
		{
			// printf("join\n");
			put_tab(cmd, cmd->next);
			// token = token->next;
		}
		// else if (!token->next && cmd && cmd->next && token->type != REDIRECT_OUT && token->type != REDIRECT_APPEND &&token->type != HERE_DOC  &&  token->type != PIPE && token->type != REDIRECT_IN && cmd->next && cmd->type != IN_OUT_FILENAME) 
		// {
		// 	put_tab(cmd, cmd->next);
			
		// 	// token = token->next;
		// }
		// else if (cmd->tab == NULL)
		// 	cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		// else

		// printf("next %s\n", cmd->value);
		// if (token->next && (token->next->type == REDIRECT_OUT || token->next->type == REDIRECT_APPEND))
		// {
		// 	if (cmd->next)
		// 		cmd = cmd->next;
		// }
		// if (token->next && token->next->type == PIPE)
		// {
		// 	// printf("idkkk %s\n", cmd->value);
		// 	cmd = cmd->next;
		// 	token = token->next;
		// 	token = token->next;
		// 	continue;
		// }
		if (token && cmd->next && (ft_check_type(token) == 1))
		{
			cmd = cmd->next;
			if (token->next->type == REDIRECT_OUT || token->next->type == REDIRECT_APPEND)
			{
				cmd = cmd->next;
				token = token->next->next;
			}
			// printf("nddd %s\n", cmd->value);
			// token = token->next;
			// continue;
		}
		// if (cmd->type != IN_OUT_FILENAME || (cmd->next && cmd->next->type == IN_OUT_FILENAME))
		token = token->next;
			
	}
	rest_tab(cpy_token, cpy_cmd);
}
