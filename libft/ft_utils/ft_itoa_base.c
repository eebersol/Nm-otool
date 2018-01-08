/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:02:34 by qdequele          #+#    #+#             */
/*   Updated: 2015/12/08 10:42:41 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// char	*ft_itoa_base(int nb, int base)
// {
// 	char			*str;
// 	size_t			len;
// 	size_t			neg;
// 	long long int	n;

// 	n = nb;
// 	len = ft_nbrlen_base(n, base);
// 	neg = ft_isnegative(n);
// 	str = (char *)malloc(sizeof(char) * (neg + len + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	str[len + neg] = '\0';
// 	if (neg)
// 	{
// 		str[0] = '-';
// 		n = -n;
// 	}
// 	while ((len-- + neg) > neg)
// 	{
// 		str[len + neg] = (n % base) + ((n % base) > 9 ? 'A' - 10 : '0');
// 		n = n / base;
// 	}
// 	return (str);
// }

#define ABS(abs) ((abs) < 0 ? (-abs) : (abs))

void	aux(int n, int b, char *ans, int *p)
{
	char	base[] = "0123456789ABCDEF";

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