/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:05:29 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:59 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	if (s != NULL && f != NULL)
	{
		while (*s)
		{
			f(s);
			s++;
		}
	}
}
