/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_raw_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 17:08:26 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:52:49 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** NAME : ft_count_raw_aoc (unnoficial)
** DESCRIPTION : Compte le nombre de lignes dans un tableau de caracteres
** PARAM : Le tableau de caractere dont il faut compter les lignes
** RETURN : Le nombre de lignes dans le tableau
*/

int		ft_count_raw_aoc(char **tab)
{
	int		i;

	i = 0;
	if (tab && *tab)
		while (tab[i])
			i++;
	return (i);
}

/*
** NAME : ft_count_raw_aos (unnoficial)
** DESCRIPTION : Compte le nombre de lignes dans un tableau de chaine de
** caracteres
** PARAM : Le tableau de chaine de caractere dont il faut compter les lignes
** RETURN : Le nombre de lignes dans le tableau
*/

int		ft_count_raw_aos(char ***tab)
{
	int		i;

	i = 0;
	if (tab && *tab)
		while (tab[i])
			i++;
	return (i);
}

/*
** NAME : ft_count_raw_aoi (unnoficial)
** DESCRIPTION : Compte le nombre de lignes dans un tableau d'entier
** PARAM : Le tableau d'entiers dont il faut compter les lignes
** RETURN : Le nombre de lignes dans le tableau
*/

int		ft_count_raw_aoi(int **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
