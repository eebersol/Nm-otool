/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 11:56:27 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/nm-otool.h"

int		switch_hexa(int x)
{
	if (0 <= x && x <= 9)
		return (48 + x);
	if (x >= 10 && x <= 15)
	{
		x = x - 10;
		return (97 + x);
	}
	return (0);
}

char			*ft_hexa_itoa(unsigned long n)
{
	char				*str;
	int					size;
	unsigned long long	x;
	int					j;

	x = n;
	j = 0;
	size = 0;
	if (x == 0)
		return ("0");
	while (x >= 16)
	{
		x /= 16;
		size++;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str)
	{
		str[size + 1] = '\0';
		while (size >= 0)
		{
			x = n % 16;
			str[size] = switch_hexa(x);
			n /= 16;
			size--;
		}
	}
	return (str);
}