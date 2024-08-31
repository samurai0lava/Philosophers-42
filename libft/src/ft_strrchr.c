/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:48:27 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/12 17:50:29 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;
	size_t			n;

	ch = (unsigned char)c;
	n = ft_strlen(s);
	i = n - 1;
	while (i < n)
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i--;
	}
	if (ch == 0 && s[n] == 0)
		return ((char *)&s[n]);
	return (NULL);
}
