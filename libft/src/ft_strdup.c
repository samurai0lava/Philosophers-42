/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:54:04 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/14 18:13:52 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;	

	dst = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}
