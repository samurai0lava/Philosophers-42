/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:32:05 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/13 16:21:44 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	digit_count;
	char	*result;
	long	nb;

	nb = (long)n;
	digit_count = count_digits(nb);
	result = (char *)malloc(digit_count + 1);
	if (!result)
		return (NULL);
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	result[digit_count] = '\0';
	while (nb > 0)
	{
		result[digit_count - 1] = (nb % 10) + '0';
		digit_count--;
		nb /= 10;
	}
	return (result);
}
