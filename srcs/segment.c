/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/23 15:16:19 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void	segment(struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	unsigned int				i;
	t_list						*list_tmp;

	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	i = 0;
	if (recover_base()->file_size < seg->fileoff + seg->filesize)
		print_err(ERR_CORRUPT);
	if (seg->nsects == 0)
		return ;
	while (i++ < seg->nsects)
	{
		list_tmp = (t_list *)malloc(sizeof(t_list));
		list_tmp->content = ft_strdup(sec->sectname);
		ft_lstadd(&recover_base()->list_segment, list_tmp);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
	}
}

void	segment_32(struct load_command *lc)
{
	struct segment_command	*seg;
	struct section			*sec;
	unsigned int			i;
	t_list					*list_tmp;

	seg = (struct segment_command *)lc;
	sec = (struct section *)(seg + sizeof(seg) / sizeof(void *));
	i = 0;
	if (recover_base()->file_size < seg->fileoff + seg->filesize)
		print_err(ERR_CORRUPT);
	if (seg->nsects == 0)
		return ;
	while (i++ < seg->nsects)
	{
		list_tmp = (t_list *)malloc(sizeof(t_list));
		list_tmp->content = ft_strdup(sec->sectname);
		ft_lstadd(&recover_base()->list_segment, list_tmp);
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
	}
}
