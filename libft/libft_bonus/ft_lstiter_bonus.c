/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <iouhssei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:04:20 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/23 18:42:30 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return ;
	tmp = lst;
	while (tmp)
	{
		next = tmp->next;
		f(tmp->content);
		tmp = next;
	}
}
