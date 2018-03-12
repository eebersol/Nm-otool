/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshow_x.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 17:23:19 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:18 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstshow_x(t_list *list, int x)
{
	t_list	*cur;
	char	c;
	int		i;

	i = 0;
	cur = list;
	while (i < x)
	{
		cur = cur->next;
		i++;
	}
	while (cur)
	{
		c = *((char *)cur->content);
		ft_putchar(c);
		cur = cur->next;
	}
}
