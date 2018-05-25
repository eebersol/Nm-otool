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

static void		reduce(struct nlist	*array, char *stringable, int i)
{
	t_magic			*magic;
	t_list			*tmp;

	check_function_name(array[i].n_un.n_strx, recover_base()->strsize, 123);
	if (!(magic = (t_magic*)malloc(sizeof(t_magic)))
		|| !(tmp = (t_list *)malloc(sizeof(t_list)))
			|| !(tmp->content = (t_magic*)malloc(sizeof(t_magic))))
		exit(1);
	magic->n_sect = array[i].n_sect;
	magic->name_func = stringable + endian_32(array[i].n_un.n_strx);
	magic->type = get_type(array[i].n_type, magic);
	magic->value = value_ppc(endian_32(array[i].n_value), 8);
	tmp->content = magic;
	find_best_place(recover_base(), tmp, i);
}

static void		check_corrupt_lc_command_ppc(struct load_command *lc,
								int cmd, unsigned int allcmd, int type)
{
	int i;

	i = 0;
	cmd = endian_32(cmd);
	while (i++ < cmd)
	{
		if (endian_32(lc->cmdsize) > endian_32(allcmd))
		{
			ft_putstr("One of load command extends past");
			ft_putstr("the end all load commands in the file\n");
			exit(1);
		}
		if (type == 32 && endian_32(lc->cmdsize) % 4 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		else if (type == 64 && endian_32(lc->cmdsize) % 8 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		lc = (void *)lc + endian_32(lc->cmdsize);
	}
}

void			data_magic_32_ppc(int nsyms, int i, int stroff, void *ptr)
{
	struct nlist	*array;
	char			*stringable;

	array = ptr + endian_32(i);
	if ((char*)(ptr + endian_32(i)) > recover_base()->idiot_check)
		return (print_err(ERR_CORRUPT, 0));
	stringable = ptr + endian_32(stroff);
	i = 0;
	recover_base()->list_segment = ft_lst_reverse(recover_base()->list_segment);
	nsyms = endian_32(nsyms);
	while (i < nsyms)
	{
		reduce(array, stringable, i);
		i++;
	}
}

void			solve_ppc(char *ptr, unsigned int i)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	recover_base()->type_file = 2;
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	check_corrupt_lc_command_ppc(lc, header->ncmds, header->sizeofcmds, 32);
	while (i++ < header->ncmds)
	{
		if (endian_32(lc->cmd) == LC_SEGMENT)
			recover_base()->nm == false ? pp(lc, header) : cc(lc);
		if (endian_32(lc->cmd) == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			recover_base()->strsize = endian_32(sym->strsize);
			data_magic_32_ppc(sym->nsyms, sym->symoff, sym->stroff, (void*)ptr);
			break ;
		}
		lc = (void *)lc + endian_32(lc->cmdsize);
	}
	recover_base()->nm == true ? print_nm() : 0;
	reinit_base(recover_base()->name);
}
