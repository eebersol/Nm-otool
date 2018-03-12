/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:01:24 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:01 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** NAME : strdel
** DESCRIPTION : La fonction strdel() supprime les caracteres de la chaine
** de carractere et la chaine elle meme
** PARAM : as -> la chaine de caractere a supprimer
*/

void	ft_strdel(char **as)
{
	if (as != NULL)
	{
		free(*as);
		*as = NULL;
	}
}
