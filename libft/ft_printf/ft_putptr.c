/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:24:58 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/27 21:15:13 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	ft_printhex(unsigned long nbr)
{
	char	*base_k;
	int		len;

	base_k = "0123456789abcdef";
	len = 0;
	if (nbr >= 16)
	{
		len += ft_printhex(nbr / 16);
		len += ft_putchar(base_k[nbr % 16]);
	}
	else
		len += ft_putchar(base_k[nbr % 16]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	unsigned long	n;
	int				len;

	n = (unsigned long)ptr;
	len = 0;
	len += ft_putstr("0x");
	len += ft_printhex(n);
	return (len);
}
