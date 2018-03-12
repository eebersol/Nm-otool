/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:17:19 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:21 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst);
			lst = lst->next;
		}
	}
}

void	ft_lstiter_plus(t_list *lst, void const *info,
	void (*f)(void const *info, t_list *elem))
{
	if (lst && f)
	{
		while (lst)
		{
			f(info, lst);
			lst = lst->next;
		}
	}
}

void	ft_lstiter_if(t_list *lst, void (*f)(t_list *elem),
	int (*c)(t_list *node))
{
	if (lst && f)
	{
		while (lst)
		{
			if (c(lst))
			{
				f(lst);
			}
			lst = lst->next;
		}
	}
}

void	ft_lstiter_if_plus(t_list *lst, void const *info,
	void (*f)(void const *info, t_list *elem), int (*c)(t_list *node))
{
	if (lst && f)
	{
		while (lst)
		{
			if (c(lst))
			{
				f(info, lst);
			}
			lst = lst->next;
		}
	}
}
