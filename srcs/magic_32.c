/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/25 13:44:11 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	get_data_nm_32(int nsyms, int symoff, int stroff, void *ptr)
{
	t_magic			*magic;
	struct nlist	*array;
	char			*stringable;
	int				i;

	recover_base()->magicBase = (t_magic*)malloc(sizeof(t_magic));
	magic = recover_base()->magicBase;
	array = ptr + symoff;
	stringable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		magic->content_32 = &array[i];
		magic->name_func = stringable + array[i].n_un.n_strx;
		magic->addr = ptr;
		magic->type = get_type(array[i].n_type, magic);
		magic->value = get_value_manager(magic, array[i].n_value);
		i++;
		if (i < nsyms)
		{
			magic->next = (t_magic*)malloc(sizeof(t_magic));
			magic = magic->next;
		}
	}
}

void	check_seg_32(struct load_command *lc, struct mach_header *header)
{
	unsigned int			i;
	struct section			*sec;
	struct segment_command	*seg;

	seg = (struct segment_command*)lc;
	sec = (struct section*)\
			(seg + sizeof(struct segment_command*) / sizeof(void*));
	i = 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(sec->segname, "__TEXT") == 0
			&& ft_strcmp(sec->sectname, "__text") == 0)
		{
			if (recover_base()->archive == false)
			{
				ft_putstr(recover_base()->name);
				ft_putstr(":\n");
				ft_putstr("Contents of (__TEXT,__text) section\n");
			}
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
		i++;
	}
}
void	handle_32(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	struct segment_command	*sc;
	unsigned int			i;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	sc = (void *)ptr + sizeof(*header);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			if (recover_base()->nm == false)
				check_seg_32(lc, header);
			else
				sectionAdd_32(lc);
		}
		if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			get_data_nm_32(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		sc = (void *)sc + lc->cmdsize;
	}
	print_manager();
}
