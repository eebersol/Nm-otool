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

void	handle_fat(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	uint32_t			offset;

	fat = (struct fat_header*)ptr;
	i = 0;
	arch = ((void*)ptr) + sizeof(fat);
	recover_base()->to_print = 1;
	recover_base()->is_alone = endian_32(fat->nfat_arch) == 1 ? true : false;
	while (i++ < endian_32(fat->nfat_arch))
	{
		check_power_pc(arch);
		if (endian_32(arch->cputype) == CPU_TYPE_POWERPC)
			solve_ppc(ptr + endian_32(arch->offset), 0);
		if (endian_32(arch->cputype) == CPU_TYPE_X86_64)
		{
			offset = arch->offset;
			break ;
		}
		else if (endian_32(arch->cputype) == CPU_TYPE_I386)
			offset = arch->offset;
		arch = (void*)arch + sizeof(struct fat_arch);
	}
	identify_file(ptr + endian_32(offset));
}

void	handle_archive(char *ptr)
{
	struct ar_hdr	*arch;
	int				i;

	arch = (struct ar_hdr *)(void*)(ptr + SARMAG);
	recover_base()->path_name = "";
	arch = (struct ar_hdr *)((void*)arch +
		sizeof(struct ar_hdr) + ft_atoi(arch->ar_size));
	if (recover_base()->nm == false)
		ft_putchar('\n');
	while (1)
	{
		if (ft_strstr(arch->ar_name, "__.SYMDEF SORTED")
			|| ft_strcmp(arch->ar_name, "") == 0)
			break ;
		i = get_size(arch->ar_name);
		if (ft_strcmp(recover_base()->path_name, get_name(arch->ar_name)) != 0)
		{
			recover_base()->path_name = get_name(arch->ar_name);
			identify_file((void *)arch + sizeof(struct ar_hdr) + i);
			reinit_base(recover_base()->name);
		}
		recover_base()->path_name = get_name(arch->ar_name);
		arch = (struct ar_hdr *)((void*)arch
			+ sizeof(struct ar_hdr) + ft_atoi(arch->ar_size));
	}
}

void	handle_32(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	check_corrupt_lc_command(lc, header->ncmds, header->sizeofcmds, 32);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			recover_base()->nm == false ?
				data_seg_32(lc, header) : segment_32(lc);
		if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			recover_base()->strsize = sym->strsize;
			data_magic_32(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	recover_base()->nm == true ? print_nm() : 0;
}

void	handle_64(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	unsigned int				i;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	check_corrupt_lc_command(lc, header->ncmds, header->sizeofcmds, 64);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			recover_base()->nm == false ? data_seg(lc, header) : segment(lc);
		if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			recover_base()->strsize = sym->strsize;
			data_magic(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	recover_base()->nm == true ? print_nm() : 0;
}
