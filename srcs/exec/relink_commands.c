/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relink_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njard <njard@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:22:15 by njard             #+#    #+#             */
/*   Updated: 2025/05/19 10:31:17 by njard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_tab(t_cmd *cmd, t_cmd *cpy_cmd)
{
	t_cmd	*temp;

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

void	rest_tab(t_cmd *cpy_cmd)
{
	t_cmd *cmd;
	cmd = cpy_cmd;
	while (cmd)
	{
		if (cmd->tab == NULL) 
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		cmd = cmd->next;
	}
	return ;
}

void	relink_commands(t_token *token, t_cmd *cpy_cmd)
{
	t_cmd *cmd;

	cmd = cpy_cmd;
	if (token->next && ft_check_type(token->next) == 1)
		token = token->next;
	while (token)
	{
		if (cmd->next)
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->next->value);
		else
			printf("token=%s, cmd=%s, cpy=%s\n",token->value, cmd->value, cmd->value);
		if (token->next && cmd && cmd->next && token->type != REDIRECT_OUT && token->type != REDIRECT_APPEND &&token->type != HERE_DOC  &&  token->type != PIPE && token->type != REDIRECT_IN && cmd->next && cmd->type != IN_OUT_FILENAME && ft_check_type(token->next) == 0)
		{
			printf("join\n");
			put_tab(cmd, cmd->next);
			token = token->next;
		}
		// else if (cmd->tab == NULL)
		// 	cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		// else

		printf("next %s\n", cmd->value);
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
			// printf("nddd %s\n", cmd->value);
			// token = token->next;
			// continue;
		}
		// if (cmd->type != IN_OUT_FILENAME || (cmd->next && cmd->next->type == IN_OUT_FILENAME))
		token = token->next;
			
	}
	rest_tab(cpy_cmd);
}
