/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:01:15 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/24 16:41:53 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	pre_len;
	size_t	suf_len;
	size_t	s1_len;
	size_t	new_len;
	char	*new_str;

	if (!s1 || !set)
		return (NULL);
	suf_len = 0;
	pre_len = 0;
	s1_len = ft_strlen(s1);
	while (s1[pre_len] && ft_strchr(set, s1[pre_len]))
		pre_len++;
	while (suf_len < s1_len && ft_strchr(set, s1[s1_len - suf_len - 1]))
		suf_len++;
	if (s1_len == pre_len || (set[0] == '\0' && suf_len == s1_len))
		return (ft_strdup(""));
	new_len = s1_len - pre_len - suf_len;
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1 + pre_len, new_len + 1);
	new_str[new_len] = '\0';
	return (new_str);
}
