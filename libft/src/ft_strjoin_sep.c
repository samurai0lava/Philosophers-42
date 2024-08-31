/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:05:43 by iouhssei          #+#    #+#             */
/*   Updated: 2024/03/28 14:05:47 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	flen(char **strings, int size, int sep_len)
{
	int	final_len;
	int	i;

	final_len = 0;
	i = 0;
	while (i < size)
	{
		final_len += ft_strlen(strings[i]);
		final_len += sep_len;
		i++;
	}
	final_len -= sep_len;
	return (final_len);
}

char	*ft_strjoin_sep(int size, char **strs, char *sep)
{
	int		i;
	char	*string;
	char	*d;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	string = (char *) malloc(flen(strs, size, ft_strlen(sep)) + 1);
	d = string;
	if (!d)
		return (0);
	i = 0;
	while (i < size)
	{
		ft_strcpy(d, strs[i]);
		d += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(d, sep);
			d += ft_strlen(sep);
		}
		i++;
	}
	*d = '\0';
	return (string);
}
