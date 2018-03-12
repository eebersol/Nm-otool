/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:06:23 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:52 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s2;

	s2 = s + ft_strlen(s);
	while (*s2 != (char)c && s2 != s)
		if (*s2 != (char)c)
			s2--;
	if (*s2 == (char)c)
		return ((char *)s2);
	return (NULL);
}

char	*ft_strrchr_n(const char *s, int c)
{
	const char	*s2;

	s2 = s + ft_strlen(s);
	while (*s2 != (char)c && s2 != s)
		if (*s2 != (char)c)
			s2--;
	if (*s2 == (char)c)
		return ((char *)++s2);
	return (NULL);
}
