/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_section_32.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 15:50:13 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void				add_seg_32(struct load_command *lc, t_section *section)
{
	struct section			*sec;
	struct segment_command	*seg;
	t_segment				*segment;
	unsigned int			i;

	i = 0;
	seg = (struct segment_command *)lc;
	sec = (struct section *)(seg + sizeof(seg) / sizeof(void*));
	section->seg = (t_segment*)malloc(sizeof(t_segment));
	segment = section->seg;
	while (i < seg->nsects)
	{
		segment->name = ft_strdup(sec->sectname);
		segment->nb = i == 0 ? recover_base()->index : segment->nb;
		segment->next = (t_segment*)malloc(sizeof(t_segment));
		segment->next->nb = segment->nb + 1;
		segment = segment->next;
		i++;
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
	}
	recover_base()->index = segment->nb == 0 ? 1 : segment->nb;
	segment->next = NULL;
}

unsigned int		get_end_32(struct load_command *lctmp, unsigned int len)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	printf("Len : %u\n", len);
	while (i < len)
	{
		if (lctmp->cmd == LC_SEGMENT)
		{
			count++;
		}
		printf("Size : %d\n", lctmp->cmdsize);
		if (lctmp->cmdsize >= INT_MAX)
		{
			break ;
		}
		lctmp += lctmp->cmdsize / sizeof(void *);
		i++;
	}
	return (count);
}

void				get_section_32(struct load_command *lc,
								struct mach_header *header, unsigned int len)
{
	t_section		*section;
	unsigned int	i;
	size_t			k;

	printf("HOLA\n");
	i = 0;
	k = 0;
	recover_base()->sectionBase = (t_section*)malloc(sizeof(t_section));
	section = recover_base()->sectionBase;
	printf("HOLA\n");
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			k++;
			add_seg_32(lc, section);
			if (k < len)
			{
				section->next = (t_section*)malloc(sizeof(t_section));
				section = section->next;
			}
		}
		if (lc->cmdsize >= INT_MAX)
			break ;
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
}
