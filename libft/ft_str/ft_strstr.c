/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 09:41:50 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:47 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s2[0] == '\0')
		return (char *)(s1);
	while (s1[i] != '\0')
	{
		while (s1[i + j] == s2[j])
		{
			j++;
			if (s2[j] == '\0')
				return (char *)(&s1[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
