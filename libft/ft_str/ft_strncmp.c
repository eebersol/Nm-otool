/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:39:33 by qdequele          #+#    #+#             */
/*   Updated: 2018/01/23 16:08:03 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** NAME : strncmp
** DESCRIPTION : La fonction strncmp() est identique à strcmp sauf qu'elle ne
** compare que les n (au plus) premiers caractères de s1 et s2.
** PARAM : s1 -> la premiere chaine à comparé
** PARAM : s2 -> la deuxieme chaine à comparé
** PARAM : n -> le nombre de caractere à comparer
** RETURN : entier positif, nul, ou negatif
*/

/* 
**int		ft_strncmp(const char *s1, const char *s2, size_t n)
** {
** 	size_t		i;

** 	i = 0;
** 	if (n == 0)
** 		return (0);
** 	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
** 	{
** 		i++;
** 	}
** 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
** }
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
		n--;
	}
	return (0);
}
