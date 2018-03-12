/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:14:23 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 15:06:32 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_lstcount(t_list *lst)
{
	int		i;
	t_list	*elem;

	i = 0;
	elem = lst;
	if (lst)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}
