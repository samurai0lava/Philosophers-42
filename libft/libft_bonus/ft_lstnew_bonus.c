/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:03:14 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/15 23:26:51 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cont;

	cont = (t_list *)malloc(1 * sizeof(t_list));
	if (!cont)
		return (NULL);
	cont->content = content;
	cont->next = NULL;
	return (cont);
}
