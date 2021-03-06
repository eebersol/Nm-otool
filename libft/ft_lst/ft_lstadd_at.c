/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:10:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:26 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void		ft_lstadd_at(t_list **lst, t_list *new, int at)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	if (at > ft_lstcount(tmp) || at < 0)
		return ;
	else if (at == 0)
		ft_lstadd(lst, new);
	else if (at == ft_lstcount(tmp))
		ft_lstaddend(lst, new);
	else
	{
		while (++i < at)
		{
			tmp = tmp->next;
			if (tmp == NULL)
				break ;
		}
		if (tmp != NULL)
		{
			new->next = tmp->next;
			tmp->next = new;
		}
	}
}
