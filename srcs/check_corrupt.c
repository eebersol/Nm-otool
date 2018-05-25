/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_corrupt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 13:36:52 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

static void		check_power_pc_bis(t_base *base, struct fat_arch *arch)
{
	if (endian_32(arch->cputype) == CPU_TYPE_I386)
		base->ii = true;
	if (base->nm == false)
	{
		if (endian_32(arch->cputype) == CPU_TYPE_I386)
			base->path_name = "architecture i386";
		else
			base->path_name = "architecture X86_64";
	}
	else
	{
		ft_putstr("\n");
		ft_putstr(base->name);
		endian_32(arch->cputype) == CPU_TYPE_I386 ?
			ft_putstr(" (for architecture i386):\n")
				: ft_putstr(" (for architecture X86_64):\n");
	}
}

void			check_function_name(unsigned int offset, unsigned int size,
																	int type)
{
	if (size == 0)
		print_err(ERR_BAD_INDEX, 1);
	if (type == 123)
		offset = endian_32(offset);
	if (size == 0 || offset > size)
		print_err(ERR_BAD_INDEX, 1);
	else
		return ;
}

void			check_corrupt_lc_command(struct load_command *lc,
								int cmd, unsigned int allcmd, int type)
{
	int i;

	i = 0;
	while (i++ < cmd)
	{
		if (lc->cmdsize > allcmd)
		{
			ft_putstr("One of load command extends past");
			ft_putstr("the end all load commands in the file\n");
			exit(1);
		}
		if (type == 32 && lc->cmdsize % 4 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		else if (type == 64 && lc->cmdsize % 8 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		lc = (void *)lc + lc->cmdsize;
	}
}

void			check_corruption(unsigned int offset_seg, unsigned int size_seg,
								unsigned int offset_sec, unsigned int size_sec)
{
	t_base *base;

	base = recover_base();
	if (base->file_size < offset_seg + size_seg)
		print_err(ERR_CORRUPT, 1);
	else if (offset_sec > 0 && offset_sec + size_sec > base->file_size)
		exit(1);
}

void			check_power_pc(struct fat_arch *arch)
{
	t_base	*base;

	base = recover_base();
	if (base->file_size < endian_32(arch->offset) + endian_32(arch->size)
		|| arch->offset == 0)
		print_err(ERR_CORRUPT, 1);
	if (endian_32(arch->cputype) == CPU_TYPE_POWERPC)
	{
		base->power_pc = true;
		if (base->nm == false)
		{
			base->name = ft_strjoin(base->name, " ");
			base->path_name = "architecture ppc";
		}
		else
		{
			ft_putstr("\n");
			ft_putstr(base->name);
			ft_putstr(" (for architecture ppc):\n");
		}
	}
	else if (endian_32(arch->cputype) != CPU_TYPE_POWERPC
		&& base->power_pc == true)
		check_power_pc_bis(base, arch);
}
