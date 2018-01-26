/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 16:04:20 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	handle_fat(char *ptr)
{
	struct fat_header	*fat;
	struct fat_arch		*arch;
	uint32_t			i;
	uint32_t			offset;

	fat = (void*)ptr;
	i = swap_uint32(fat->nfat_arch);
	arch = ((void*)ptr) + sizeof(fat);
	while (i--)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		else if (swap_uint32(arch->cputype) == CPU_TYPE_I386)
			return (ft_putstr("CPU_TYPE_I386 are not supported.\n"));
		else if (swap_uint32(arch->cputype) == CPU_TYPE_POWERPC)
			return (ft_putstr("CPU_TYPE_POWERPC are not supported.\n"));
		arch += sizeof(struct fat_arch);
	}
	identify_file(ptr + swap_uint32(offset));
}

void	handle_32(char *ptr)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	unsigned int			i;

	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			recover_base()->nm == false ?
						data_seg_32(lc, header) : section_32(lc);
		if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			data_magic_32(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	//print_manager();
}

void	handle_64(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	unsigned int				i;

	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (i++ < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			recover_base()->nm == false ? data_seg(lc, header) : section(lc);
		if (lc->cmd == LC_SYMTAB && recover_base()->nm == true)
		{
			sym = (struct symtab_command *)lc;
			data_magic(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	//print_manager();
}
