/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:51:17 by naankour          #+#    #+#             */
/*   Updated: 2025/05/06 18:51:17 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

union
inter
wdmatch





































unsigned char	swap_bits (unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}

void	print_bits(unsigned char octet)
{
	int	i;
	unsigned char bit;

	i = 8;
	while(i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}
































unsigned char reverse_bits(unsigned char octet)
{
	unsigned char result = 0;
	int i = 0;

	while (i < 8)
	{
		result = result * 2 + (octet % 2);
		octet = octet / 2;
		i++;
	}
	return result;
}





















































// unsigned char	swap_bits (unsigned char octet)
// {
// 	return ((octet >> 4) | (octet << 4));
// }

// void	print_bits(unsigned char octet)
// {
// 	int	i;
// 	unsigned char bit;

// 	i = 8;
// 	while(i--)
// 	{
// 		bit = (octet >> i & 1) + '0';
// 		write(1, &bit, 1);
// 	}
// }