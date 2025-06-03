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

static int	ft_condition_one(t_token *cpy_token)
{
	if (!cpy_token || !cpy_token->next || cpy_token->type == PIPE
		|| !cpy_token->next->next)
		return (1);
	return (0);
}

static void	ft_delete_intermediate_tokens(t_token *prev_node,
		t_token *current_node)
{
	t_token	*to_delete;
	t_token	*next_to_delete;

	if (!prev_node)
		return ;
	to_delete = prev_node->next;
	while (to_delete && to_delete != current_node)
	{
		next_to_delete = to_delete->next;
		ft_free_single_token(to_delete);
		to_delete = next_to_delete;
	}
}

static void	ft_process_and_relink(t_token **current_node,
		t_token *word_start_node, t_token **temp, t_cmd *cmd)
{
	t_cmd	*cmd_for_current;
	t_cmd	*cmd_for_word_start;

	cmd_for_current = find_cmd_index(*current_node, cmd);
	if (!cmd_for_current)
	{
		*current_node = (*current_node)->next;
		return ;
	}
	cmd_for_word_start = find_cmd_index(word_start_node, cmd);
	if (!cmd_for_word_start)
	{
		*current_node = (*current_node)->next;
		return ;
	}
	put_tab_recompose(cmd_for_word_start, cmd_for_current);
	ft_delete_intermediate_tokens(*temp, *current_node);
	(*temp)->next = *current_node;
	*temp = (*temp)->next;
	if (*temp)
		*current_node = (*temp)->next;
	else
		*current_node = NULL;
}

static void	ft_handle_processing_loop(t_token **current_node,
		t_token *word_start_node, t_token **temp, t_cmd *cmd)
{
	while (*current_node && ft_check_type(*current_node) == 0)
	{
		ft_process_and_relink(current_node,
			word_start_node,
			temp,
			cmd);
	}
}

void	ft_process_word_type_token(t_token **current_node, t_cmd *cmd)
{
	t_token	*word_start_node;
	t_token	*temp;

	word_start_node = *current_node;
	temp = *current_node;
	ft_skip_words(current_node, &temp);
	if (ft_condition_one(*current_node) == 1)
	{
		if (*current_node && (*current_node)->next)
			*current_node = (*current_node)->next;
		return ;
	}
	else
	{
		while (*current_node && (*current_node)->type != WORD
			&& (*current_node)->type != SINGLE_QUOTES
			&& (*current_node)->type != DOUBLE_QUOTES && (*current_node)->next)
			*current_node = (*current_node)->next->next;
	}
	ft_handle_processing_loop(current_node, word_start_node, &temp, cmd);
	return ;
}
