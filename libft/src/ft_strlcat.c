/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:05:01 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/23 20:53:58 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t sz)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if (dst == NULL && sz == 0)
		return (0);
	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (sz <= dstlen)
		return (sz + srclen);
	while (dstlen + i < sz - 1 && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
