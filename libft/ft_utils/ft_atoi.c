/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:43:46 by qdequele          #+#    #+#             */
/*   Updated: 2018/02/20 16:41:51 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_atoi(const char *s)
{
	int		v;
	int		i;
	int		n;

	v = 0;
	i = 0;
	n = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' ||
		s[i] == '\v' || s[i] == '\r' || s[i] == '\f')
		i++;
	if ((s[i] == '+' || s[i] == '-') && (s[i + 1] >= '0' && s[i + 1] <= '9'))
	{
		if (s[i] == '-')
			n = 1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9' && s[i])
	{
		if ((v * 10 + s[i]) > 2147483647)
			v = 2147483647;
		else
			v = v * 10 + (s[i] - '0');
		i++;
	}
	return ((n) ? -v : v);
}
