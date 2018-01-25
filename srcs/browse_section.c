/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/24 14:51:11 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char		browse_section_32(t_magic *magic)
{
	t_section	*tmp;
	char		c;

	tmp = recover_base()->sectionBase;
	c = 'X';
//	printf("\f-Begin %d\n", lst_count_section(recover_base()->sectionBase));
	while (tmp)
	{
		//printf("\t-In :\n");
		//printf("\t\tLen : %d\n",  lst_count_segment(tmp->seg));
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
	//printf("ICI : %d\n", lst_count_segment(recover_base()->sectionBase->seg));
	//printf("ICI : %d\n", lst_count_segment(recover_base()->sectionBase->next->seg));
	//printf("ICI : %d\n", lst_count_segment(recover_base()->sectionBase->next->next->seg));
	//printf("Len section in browse_section :: %d\n", lst_count_section(tmp));
	c = 'X';
	//printf("\f-Begin %d\n", lst_count_section(recover_base()->sectionBase));
	while (tmp)
	{
		//printf("\t-In :\n");
		//printf("\t\tLen : %d\n",  lst_count_segment(tmp->seg));
		c = get_char(tmp->seg, magic);
		if (c != 'X')
			return (c);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	//printf("\t-End\n");
	return ('S');
}
