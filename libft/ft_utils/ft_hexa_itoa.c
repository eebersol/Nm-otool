/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/20 16:44:02 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int			make_size(unsigned long long x)
{
	int	size;

	size = 0;
	while (x >= 16)
	{
		x /= 16;
		size++;
	}
	return (size);
}

static int			switch_hexa(int x)
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

char				*ft_hexa_itoa(unsigned long n)
{
	char				*str;
	int					size;
	unsigned long long	x;

	x = n;
	size = 0;
	if (n == 0)
		return ("0");
	size = make_size(x);
	str = (char *)malloc(sizeof(char) * (size + 1));
	str[size + 1] = '\0';
	while (size >= 0)
	{
		x = n % 16;
		str[size] = switch_hexa(x);
		n /= 16;
		size--;
	}
	return (str);
}
