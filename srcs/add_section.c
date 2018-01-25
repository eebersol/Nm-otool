/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/24 13:24:56 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void			add_seg(struct load_command *lc, t_section *section)
{
	struct section_64			*sec;
	struct segment_command_64	*seg;
	unsigned int				i;
	t_segment					*segment;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	section->seg = (t_segment *)malloc(sizeof(t_segment));
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment->name = ft_strdup(sec->sectname);
		segment->nb = i == 0 ? recover_base()->index : segment->nb;
		segment->next = (t_segment*)malloc(sizeof(t_segment));
		segment->next->nb = segment->nb + 1;
		segment = segment->next;
		i++;
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
	}
	recover_base()->index = segment->nb == 0 ? 1 : segment->nb;
	segment->next = NULL;
}

unsigned int	get_end(struct load_command *lctmp, unsigned int len)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (lctmp->cmd == LC_SEGMENT_64)
			count++;
		lctmp += lctmp->cmdsize / sizeof(void *);
		i++;
	}
	return (count);
}

void			get_section(struct load_command *lc,
								struct mach_header_64 *header, unsigned int len)
{
	t_section		*section;
	unsigned int	i;
	size_t			k;

	i = 0;
	k = 0;
	recover_base()->sectionBase = (t_section*)malloc(sizeof(t_section));
	section = recover_base()->sectionBase;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			k++;
			add_seg(lc, section);
			if (k < len)
			{
				section->next = (t_section*)malloc(sizeof(t_section));
				section = section->next;
			}
			else
				section->next = NULL;
		}
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
}
