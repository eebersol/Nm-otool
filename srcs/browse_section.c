/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 16:04:47 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char		browse_section_32(t_magic *magic)
{
	t_section	*tmp;
	char		c;

	tmp = recover_base()->sectionBase;
	c = 'X';
	while (tmp)
	{
		c = get_char_32(tmp->seg, magic);
		if (c != 'X')
			return (c);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return ('S');
}

char		browse_section(t_magic *magic)
{
	t_section	*tmp;
	char		c;

	tmp = recover_base()->sectionBase;
	c = 'X';
	while (tmp)
	{
		c = get_char(tmp->seg, magic);
		if (c != 'X')
			return (c);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return ('S');
}
