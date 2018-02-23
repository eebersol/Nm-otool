/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:02:34 by qdequele          #+#    #+#             */
/*   Updated: 2018/02/22 11:39:23 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#define ABS(abs) ((abs) < 0 ? (-abs) : (abs))

void	aux(int n, int b, char *ans, int *p)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (n <= -b || b <= n)
		aux(n / b, b, ans, p);
	ans[(*p)++] = base[ABS(n % b)];
}

char	*ft_itoa_base(int value, int base)
{
	char	*ans;
	int		p;

	if (base < 2 || 16 < base
		|| !(ans = (char *)malloc(sizeof(char) * 35)))
		return (NULL);
	p = 0;
	if (base == 10 && value < 0)
		ans[p++] = '-';
	aux(value, base, ans, &p);
	ans[p] = '\0';
	return (ans);
}

char	*ft_ultohex(unsigned long nb)
{
	char			*str;
	size_t			len;

	len = ft_ullen_base(nb, 16);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = (nb % 16) + ((nb % 16) > 9 ? 'a' - 10 : '0');
		nb = nb / 16;
	}
	return (str);
}
