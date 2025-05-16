/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_from_libft3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:46:24 by naankour          #+#    #+#             */
/*   Updated: 2025/05/13 17:46:24 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long	ft_nlen(long n)
{
	long	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len ++;
		n = n * (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static void	*ft_mem(long len)
{
	char	*str;

	str = (char *) malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long	len;
	char	*str;
	long	num;

	num = n;
	len = ft_nlen(n);
	str = ft_mem(len);
	str[len] = '\0';
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (num < 0)
	{
		str[0] = '-';
		num = num * (-1);
	}
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}
