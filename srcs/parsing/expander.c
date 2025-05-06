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

// je parcours les tokens, chaque fois que j'ai un token word je regarde s'il y a un $,
// si je le trouve je skip le $ et je copie ce qui suit tant que c'est un caractere alphanumérique ou un _
// j'ai le nom de la variable
// avec getenv je cherche dans l'env le nom de cette variable stockée dans value


// maintenant je dois récuperer la totalité du token le copier et afficher la value a la place de la variable
// a la fin remplacer current->value par le contenu du nouveau buffer

void	expander(t_token *token)
{
	t_token	*current;
	char	*str;
	char	name[128];
	char	*value;
	int		i;
	char	*final_buffer;

	current = token;
	while (current)
	{
		if ((current->type == WORD) && ft_strchr(current->value, '$'))
		{
			// printf("heeerreee\n");
			// printf("%s\n", current->value);
			str = current->value;
			// printf("%s\n", str);
			i = 0;
			while(*str)
			{
				if (*str == '$')
				{
					// printf("$ : %c\n", *str);
					str++;
					// printf("$ : %c\n", *str);
					i = 0;
					while (ft_isalnum(*str) || *str == '_')
					{
						// printf("%c\n", *str);
						name[i++] = *str++;
					}
					name[i] = '\0';
					// printf("name = %s\n", name);
					value = getenv(name);
					if (value)
					printf("value = %s\n", value);
				}
				else
				{
					// printf("heeeerrreeee3\n");
					str++;
				}
			}

		}
		current = current->next;
	}
}

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