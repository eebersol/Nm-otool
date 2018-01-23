/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 12:40:08 by eebersol         ###   ########.fr       */
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
		{
			ft_putstr("CPU_TYPE_I386 are not supported.\n");
			return ;
		}
		else if (swap_uint32(arch->cputype) == CPU_TYPE_POWERPC)
		{
			ft_putstr("CPU_TYPE_POWERPC are not supported.\n");
			return ;
		}
		arch += sizeof(struct fat_arch);
	}
	identify_file(ptr + swap_uint32(offset));
}
