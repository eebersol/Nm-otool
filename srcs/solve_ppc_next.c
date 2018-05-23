/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 12:40:24 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void	data_magic_32_ppc(int nsyms, int symoff, int stroff, int strsize, void *ptr)
{
	t_list			*tmp;
	t_magic			*magic;
	struct nlist	*array;
	char			*stringable;
	int				i;

	array = ptr + endian_32(symoff);
	stringable = ptr + endian_32(stroff);
	i = 0;
	(void)strsize;
	recover_base()->list_segment = ft_lst_reverse(recover_base()->list_segment);
	nsyms = endian_32(nsyms);
	while (i < nsyms)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		magic = (t_magic*)malloc(sizeof(t_magic));
		magic->n_sect = array[i].n_sect;
		magic->name_func = stringable + endian_32(array[i].n_un.n_strx);
		magic->type = get_type(array[i].n_type, magic);
		magic->value = value_ppc(endian_32(array[i].n_value), 8);
		tmp->content = (t_magic*)malloc(sizeof(t_magic));
		tmp->content = magic;
		find_best_place(recover_base(), tmp, i);
		i++;
	}
}

void  solve_ppc(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;

	recover_base()->type_file = 2;
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (endian_32(lc->cmd) == LC_SEGMENT)
		{
			recover_base()->nm == false ?
				data_seg_32_ppc(lc, header) : segment_ppc(lc);
		}
		if (endian_32(lc->cmd) == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			data_magic_32_ppc(sym->nsyms, sym->symoff, sym->stroff, sym->strsize, (void *)ptr);
			break ;
		}
		lc = (void *)lc + endian_32(lc->cmdsize);
	}
	recover_base()->nm == true ? print_nm() : 0;
	// recover_base()->list_segment = ft_lst_reverse(recover_base()->list_segment);
	reinit_base(recover_base()->name);
}
