/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:31:17 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:09 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr(char const *s)
{
	while (*s)
	{
		ft_putchar(*s);
		s = s + 1;
	}
}

void	ft_putstr_c(char *color, char const *s)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putstr("\e[0m");
}
