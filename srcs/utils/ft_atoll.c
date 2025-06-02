/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:33:32 by naankour          #+#    #+#             */
/*   Updated: 2025/06/02 17:33:32 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_overflow(long long num, int sign, char digit)
{
	if (sign == 1 && num > ((LLONG_MAX - (digit - '0')) / 10))
		return (1);
	if (sign == -1 && (-num) < (LLONG_MIN + (digit - '0')) / 10)
		return (1);
	return (0);
}

int	ft_atoll(char *str, long long *result)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	skip_whitespaces(str, &i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(num, sign, str[i]))
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*result = num * sign;
	return (1);
}
