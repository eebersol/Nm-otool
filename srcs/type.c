/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/20 16:35:48 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

char		get_char(char *name)
{
	if (!name)
		return ('X');
	if (ft_strcmp(name, SECT_BSS) == 0)
		return ('B');
	else if (ft_strcmp(name, SECT_DATA) == 0)
		return ('D');
	else if (ft_strcmp(name, SECT_TEXT) == 0)
		return ('T');
	else
		return ('S');
}

char		get_type(uint8_t n_type, t_magic *magic)
{
	char	c;
	t_list	*list;

	if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		list = ft_lstget_at(recover_base()->list_segment,
			(int)magic->n_sect - 1);
		c = get_char((char*)list->content);
	}
	else if ((n_type & N_TYPE) == N_PBUD)
		c = 'S';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else
		c = 'X';
	if ((n_type & N_EXT) == 0 && c != 'X')
		c += 32;
	return (c);
}
