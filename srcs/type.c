/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/23 15:37:05 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void		check_power_pc(struct fat_header *fat, struct fat_arch *arch)
{
	t_base	*base;

	base = recover_base();

	if (arch->offset == 0)
		return ;
	// if (endian_32(arch->cputype) == CPU_TYPE_POWERPC)
	// 	printf("power_pc\n");
	// if (endian_32(arch->cputype) == CPU_TYPE_X86_64)
	// 	printf("X86_64\n");
	// if (endian_32(arch->cputype) == CPU_TYPE_I386)
	// 	printf("I386\n");
	// printf("offset : %u\n", arch->offset);
	if (endian_32(fat->nfat_arch) == 1 && endian_32(arch->cputype) == CPU_TYPE_POWERPC)
		print_err(ERR_POWER_PC);
	else if (endian_32(fat->nfat_arch) != 1
		&& endian_32(arch->cputype) == CPU_TYPE_POWERPC)
	{
		base->power_pc = true;
		ft_putstr("\n");
		ft_putstr(base->name);
		ft_putstr(" (for architecture ppc):\n Not supported.");
	}
	else if (endian_32(arch->cputype) != CPU_TYPE_POWERPC
		&& base->power_pc == true)
	{
		ft_putstr("\n");
		ft_putstr(base->name);
		endian_32(arch->cputype) == CPU_TYPE_I386 ?
			ft_putstr(" (for architecture i386):\n")
				: ft_putstr(" (for architecture X86_64):\n");
	}
}

char		get_char(char *name)
{
	if (!name)
		return ('X');
	if (ft_strcmp(name, SECT_BSS) == 0)
		return ('B');
	else if (ft_strcmp(name, SECT_DATA) == 0)
		return ('D');
	else if (ft_strcmp(name, SECT_TEXT) == 0)
		return ('T');
	else
		return ('S');
}

char		get_type(uint8_t n_type, t_magic *magic)
{
	char	c;
	t_list	*list;

	if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT)
	{
		list = ft_lstget_at(recover_base()->list_segment,
			(int)magic->n_sect - 1);
		c = get_char((char*)list->content);
	}
	else if ((n_type & N_TYPE) == N_PBUD)
		c = 'S';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else
		c = 'X';
	if ((n_type & N_EXT) == 0 && c != 'X')
		c += 32;
	return (c);
}
