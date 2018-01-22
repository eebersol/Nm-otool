/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 17:15:48 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	get_data_nm(int nsyms, int symoff, int stroff, void *ptr)
{
	t_magic			*magic;
	struct nlist_64 *array;
	char			*stringable;
	int				i;

	recover_base()->magicBase = (t_magic*)malloc(sizeof(t_magic));
	magic = recover_base()->magicBase;
	array = ptr + symoff;
	stringable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		magic->content = &array[i];
		magic->name_func = stringable + array[i].n_un.n_strx;
		magic->addr = ptr;
		magic->type = get_type(array[i].n_type, magic);
		magic->value = get_value(array[i].n_value);
		magic->value_number = swap_uint64(array[i].n_value);
		i++;
		if (i < nsyms)
		{
			magic->next = (t_magic*)malloc(sizeof(t_magic));
			magic = magic->next;
		}
	}
}

void	check_seg(struct load_command *lc, struct mach_header_64 *header)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)\
				(seg + sizeof(struct segment_command_64*) / sizeof(void*));
	i = 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(sec->segname, "__TEXT") == 0
			&& ft_strcmp(sec->sectname, "__text") == 0)
		{
			if (recover_base()->archive == false && recover_base()->nm == false)
			{
				ft_putstr(recover_base()->name);
				ft_putstr(":\n");
				ft_putstr("Contents of (__TEXT,__text) section\n");
			}
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void	get_content(uint64_t addr, unsigned int size, char *ptr)
{
	t_magic			*magic;
	unsigned int	i;
	char			*str;

	i = 0;
	str = "";
	recover_base()->magicBase = (t_magic*)malloc(sizeof(t_magic));
	magic = recover_base()->magicBase;
	while (i < size)
	{
		if (i % 16 == 0 && i != 0)
			addr += 16;
		str = ft_strjoin(ft_strjoin(str, itoa_base(ptr[i], 16, 2)), " ");
		if ((i + 1) % 16 == 0)
		{
			if (i + 1 != size)
				magic = add_list(magic, str, val_otool(swap_uint64(addr)), 0);
			if (i + 1 == size)
				break ;
			str = "";
		}
		i++;
	}
	if (str && ft_strlen(str) > 1 && magic->text_section == NULL)
		magic = add_list(magic, str, val_otool(swap_uint64(addr)), 1);
}

void	handle_64(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	struct segment_command_64	*sc;
	unsigned int				i;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	sc = (void *)ptr + sizeof(*header);
	i = 0;
	get_section(lc, header, get_end(lc, header->ncmds));
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64 && recover_base()->nm == false)
			check_seg(lc, header);
		else if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			get_data_nm(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		sc = (void *)sc + lc->cmdsize;
	}
	print_manager();
}
