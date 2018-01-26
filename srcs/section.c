/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 15:16:06 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

t_segment	 *segment_add(t_segment *segment, int i, char *sectname, int typeFile, int len)
{
	segment->name = ft_strdup(sectname);
	segment->nb = i == 0 ? recover_base()->index : segment->nb;
	if (i+1 < len && typeFile == 32)
	{
		segment->next = (t_segment*)malloc(sizeof(t_segment));
		segment->next->nb = segment->nb + 1;
		segment = segment->next;
	}
	else if (typeFile == 64)
	{
		segment->next = (t_segment*)malloc(sizeof(t_segment));
		segment->next->nb = segment->nb + 1;
		segment = segment->next;
	}
	return (segment);
}

t_section	 *section_add(void)
{
	t_section 	*section;
	t_base 		*base;

	base = recover_base();
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
	return (section);
}

void 	section(struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	unsigned int 				i;
	t_section 					*section;
	t_segment 					*segment;

	seg 	= (struct segment_command_64 *)lc;
	sec 	= (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	i 		= 0;
	if (seg->nsects == 0)
		return;
	section = section_add();
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment = segment_add(segment, i, sec->sectname, 64,  seg->nsects);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
	recover_base()->index = segment->nb == 0 ? 1 : segment->nb;
	section->next = NULL;
	segment->next = NULL;
}

void 	section_32(struct load_command *lc)
{
	struct segment_command		*seg;
	struct section				*sec;
	unsigned int 				i;
	t_section 					*section;
	t_segment 					*segment;

	seg 	= (struct segment_command *)lc;
	sec 	= (struct section *)(seg + sizeof(seg) / sizeof(void *));
	i 		= 0;
	if (seg && seg->nsects == 0)
	{
		return;
	}
	section = section_add();
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment = segment_add(segment, i, sec->sectname, 32,  seg->nsects);
		i++;
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
	}
	recover_base()->index = segment->nb == 0 ? 1 : segment->nb;
	section->next = NULL;
	segment->next = NULL;
}