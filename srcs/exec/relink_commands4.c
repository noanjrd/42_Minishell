/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   relink_commands3.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: njard <njard@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/12 14:22:15 by njard			 #+#	#+#			 */
/*   Updated: 2025/06/02 11:21:03 by njard			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rest_tab(t_token *token, t_cmd *cpy_cmd)
{
	t_cmd	*cmd;

	cmd = cpy_cmd;
	while (cmd)
	{
		if (cmd->tab == NULL)
			cmd->tab = ft_join_tab(cmd->tab, NULL, cmd->value);
		cmd = cmd->next;
	}
	ft_check_echo_plus(token, cpy_cmd);
	return ;
}

void	ft_skip_words(t_token **t, t_token **temp_arg)
{
	t_token	*temp2;
	t_token	*cpy_token;

	temp2 = *t;
	cpy_token = *temp_arg;
	while (cpy_token && ft_check_type(cpy_token) == 0)
	{
		cpy_token = cpy_token->next;
		if (temp2->next && ft_check_type(temp2->next) == 0)
			temp2 = temp2->next;
	}
	*t = cpy_token;
	*temp_arg = temp2;
}

void	ft_check_echo_plus(t_token *token, t_cmd *cmd)
{
	t_token	*current_token;

	current_token = token;
	while (current_token)
	{
		if (current_token->type == WORD)
			ft_process_word_type_token(&current_token, cmd);
		else
			current_token = current_token->next;
	}
	return ;
}
