/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 10:14:23 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:24 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstcpy(t_list **dest, t_list *src)
{
	while (src)
	{
		ft_lstaddend(dest, ft_lstnew(src->content, src->content_size));
		src = src->next;
	}
}
