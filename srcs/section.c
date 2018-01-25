/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/24 14:53:11 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void 	sectionAdd(struct load_command *lc)
{
	t_section 					*section;
	t_base 						*base;
	t_segment 					*segment;
	struct segment_command_64	*seg;
	struct section_64			*sec;
	unsigned int 				i;
	base 	= recover_base();
	seg 	= (struct segment_command_64 *)lc;
	sec 	= (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	i 		= 0;
	if (seg->nsects == 0)
		return;
	if (!base->sectionBase)
	{
		base->sectionBase = (t_section*)malloc(sizeof(t_section));
		base->sectionBase->seg = (t_segment*)malloc(sizeof(t_segment));
		section = base->sectionBase;
		section->seg = base->sectionBase->seg;
	}
	else
	{
		section = base->sectionBase;
		while (section)
		{
			if (section->next == NULL)
				break;
			section = section->next;
		}
		section->next = (t_section*)malloc(sizeof(t_section));
		section->next->seg = (t_segment*)malloc(sizeof(t_segment));
		section = section->next;
	}
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment->name = ft_strdup(sec->sectname);
		segment->nb = i == 0 ? recover_base()->index : segment->nb;
		i++;
		// if (i < seg->nsects)
		// {
			segment->next = (t_segment*)malloc(sizeof(t_segment));
			segment->next->nb = segment->nb + 1;
			segment = segment->next;
		// }
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
	}
	base->index = segment->nb == 0 ? 1 : segment->nb;
	section->next = NULL;
	segment->next = NULL;
}

void 	sectionAdd_32(struct load_command *lc)
{
	t_section 					*section;
	t_base 						*base;
	t_segment 					*segment;
	struct segment_command		*seg;
	struct section				*sec;
	unsigned int 				i;
	base 	= recover_base();
	seg 	= (struct segment_command *)lc;
	sec 	= (struct section *)(seg + sizeof(seg) / sizeof(void *));
	i 		= 0;
	if (seg && seg->nsects == 0)
		return;
	if (!base->sectionBase)
	{
		base->sectionBase = (t_section*)malloc(sizeof(t_section));
		base->sectionBase->seg = (t_segment*)malloc(sizeof(t_segment));
		section = base->sectionBase;
		section->seg = base->sectionBase->seg;
	}
	else
	{
		section = base->sectionBase;
		while (section)
		{
			if (section->next == NULL)
				break;
			section = section->next;
		}
		section->next = (t_section*)malloc(sizeof(t_section));
		section->next->seg = (t_segment*)malloc(sizeof(t_segment));
		section = section->next;
	}
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment->name = ft_strdup(sec->sectname);;
		segment->nb = i == 0 ? base->index : segment->nb;
		i++;
		if (i < seg->nsects)
		{
			segment->next = (t_segment*)malloc(sizeof(t_segment));
			segment->next->nb = segment->nb + 1;
			segment = segment->next;
		}
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
	}
	base->index = segment->nb == 0 ? 1 : segment->nb;
	section->next = NULL;
	segment->next = NULL;
}