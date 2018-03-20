/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_magic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 12:44:20 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void	data_magic(int nsyms, int symoff, int stroff, void *ptr)
{
	t_list			*tmp;
	t_magic			*magic;
	struct nlist_64 *array;
	char			*stringable;
	int				i;

	array = ptr + symoff;
	stringable = ptr + stroff;
	i = 0;
	recover_base()->list_segment = ft_lst_reverse(recover_base()->list_segment);
	while (i < nsyms)
	{
		magic = (t_magic*)malloc(sizeof(t_magic));
		magic->n_sect = array[i].n_sect;
		magic->name_func = stringable + array[i].n_un.n_strx;
		magic->type = get_type(array[i].n_type, magic);
		magic->value = ft_strdup(value_manager(magic->type, array[i].n_value));
		tmp = (t_list *)malloc(sizeof(t_list));
		tmp->content = (t_magic*)malloc(sizeof(t_magic));
		tmp->content = (void*)magic;
		find_best_place(recover_base(), tmp, i);
		i++;
	}
}

void	data_magic_32(int nsyms, int symoff, int stroff, void *ptr)
{
	t_list			*tmp;
	t_magic			*magic;
	struct nlist	*array;
	char			*stringable;
	int				i;

	array = ptr + symoff;
	stringable = ptr + stroff;
	i = 0;
	recover_base()->list_segment = ft_lst_reverse(recover_base()->list_segment);
	while (i < nsyms)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		magic = (t_magic*)malloc(sizeof(t_magic));
		magic->n_sect = array[i].n_sect;
		magic->name_func = stringable + array[i].n_un.n_strx;
		magic->type = get_type(array[i].n_type, magic);
		magic->value = value_manager(magic->type, array[i].n_value);
		tmp->content = (t_magic*)malloc(sizeof(t_magic));
		tmp->content = magic;
		find_best_place(recover_base(), tmp, i);
		i++;
	}
}

void	get_content(uint64_t addr, unsigned int size, char *ptr)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = "";
	while (i < size)
	{
		if (i % 16 == 0 && i != 0)
			addr += 16;
		str = ft_strjoin(ft_strjoin(str, itoa_base(ptr[i], 16, 2)), " ");
		if ((i + 1) % 16 == 0)
		{
			if (i + 1 != size)
				add_list(str, val_otool(endian_64(addr)));
			else
				break ;
			str = "";
		}
		i++;
	}
	if (str && ft_strlen(str) > 1)
		add_list(str, val_otool(endian_64(addr)));
}

void	data_seg(struct load_command *lc, struct mach_header_64 *header)
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
			ft_putstr(recover_base()->name);
			if (recover_base()->path_name)
			{
				ft_putstr("(");
				ft_putstr(ft_strjoin(recover_base()->path_name, ")"));
			}
			ft_putstr(":\nContents of (__TEXT,__text) section\n");
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void	data_seg_32(struct load_command *lc, struct mach_header *header)
{
	unsigned int			i;
	struct section			*sec;
	struct segment_command	*seg;

	seg = (struct segment_command*)lc;
	sec = (struct section*)\
			(seg + sizeof(struct segment_command*) / sizeof(void*));
	i = 0;
	while (i < seg->nsects && seg->nsects != 0)
	{
		if (ft_strcmp(sec->segname, "__TEXT") == 0
			&& ft_strcmp(sec->sectname, "__text") == 0)
		{
			ft_putstr(recover_base()->name);
			ft_putstr("(");
			ft_putstr(recover_base()->path_name);
			ft_putstr(")");
			ft_putstr("\nContents of (__TEXT,__text) section\n");
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
		i++;
	}
}
