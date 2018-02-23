/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 10:32:29 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/22 11:39:22 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

double	ft_sqrt(double nb)
{
	unsigned int i;
	unsigned int sq;

	i = 1;
	sq = 1;
	if ((unsigned int)nb == 0)
		return (0);
	while (i * i < (unsigned int)nb)
		i++;
	if (((unsigned int)nb % i) == 0)
		return (i);
	else
		return (0);
}
