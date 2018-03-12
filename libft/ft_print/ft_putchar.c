/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:12:26 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:12 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_c(char *color, char c)
{
	ft_putstr(color);
	ft_putchar(c);
	ft_putstr("\e[0m");
}
