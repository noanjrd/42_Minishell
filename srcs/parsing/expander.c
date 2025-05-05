/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:38 by naankour          #+#    #+#             */
/*   Updated: 2025/05/05 13:36:38 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//lettres chiffres et underscore

// void	expander(t_token *token)
// {
// 	t_token	*current;

// 	current = token;
// 	while (current)
// 	{
// 		if ((current->type == WORD) && ft_strchr(current->value = '$'))
// 		{

// 		}
// 	}
// }

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $1

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $123
// 23
// naankour@c1r3p4:~/Documents/Minishellbis$ echo $dfjkslkgfjsw

// naankour@c1r3p4:~/Documents/Minishellbis$ echo $658
// 58



// t_token	*create_token_variable(char *line, int *index)
// {
// 	int		i;
// 	char	*variable;
// 	int		len;
// 	int		start;

// 	start = *index;
// 	i = start + 1;
// 	len = 0;
// 	i = *index;
// 	variable = malloc(ft_strlen(&line[i]) + 1);
// 	if (!variable)
// 		return (NULL);
// 	i++;
// 	printf("%c", line[i]);
// 	while (ft_isalnum(line[i]) || line[i] == '_')
// 		i++;
// 		variable[len++] = line[i++];
// 	variable[len] = '\0';
// 	*index = i;
// 	return(create_token(VARIABLE, variable));
// }