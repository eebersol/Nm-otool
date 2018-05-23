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

void	check_corrupt_lc_command(struct load_command *lc, int cmd, unsigned int allcmd, int type)
{
	int i;

	i = 0;
	while (i++ < cmd)
	{
		if (lc->cmdsize > allcmd)
		{
			ft_putstr("One of load command extends past the end all load commands in the file\n");
			exit(1);
		}
		if (type == 32 && lc->cmdsize%4 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		else if (type == 64 && lc->cmdsize%8 != 0)
		{
			ft_putstr("Corrupted file.\n");
			exit(1);
		}
		lc = (void *)lc + lc->cmdsize;
		// i++;
	}
}

void check_corruption(size_t offset, size_t size_arch)
{
	t_base *base;

	base = recover_base();
	if (base->file_size < endian_32(offset) + endian_32(size_arch))
		print_err(ERR_CORRUPT);
}
