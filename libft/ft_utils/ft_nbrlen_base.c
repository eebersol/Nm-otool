/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:42:57 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:35 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_nbrlen_base(int nb, int base)
{
	int		len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / base;
	}
	return (len);
}

int		ft_ullen_base(unsigned long nb, int base)
{
	int		len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / base;
	}
	return (len);
}
