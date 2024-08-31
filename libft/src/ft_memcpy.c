/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:38 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/23 12:59:14 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst1;
	unsigned char	*src1;
	size_t			i;

	if (dst == src)
		return (dst);
	i = 0;
	src1 = (unsigned char *)src;
	dst1 = (unsigned char *)dst;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}
