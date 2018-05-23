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


char		*val_otool_ppc(uint64_t n_value)
{
	t_base	*base;
	char	*ret;

	base = recover_base();
	ret = ft_itoa_base(n_value, 16);
	return (ft_strjoin("0000", ft_str_lower(ret)));
}

void	get_content_ppc(uint32_t addr, unsigned int size, char *ptr)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = "";
	while (i < size)
	{
		if (i % 16 == 0 && i != 0)
			addr += 16;
		str = ft_strjoin(ft_strjoin(str, itoa_base(ptr[i], 16, 2)), "");
		if ((i+1)%4 == 0)
			str = ft_strjoin(str, " ");
		if ((i + 1) % 16 == 0)
		{
			if (i + 1 != size)
				add_list(str, val_otool_ppc(addr));
			else
				break ;
			str = "";
		}
		i++;
	}
	if (str && ft_strlen(str) > 1)
		add_list(str, val_otool(endian_64(addr)));
}

void	data_seg_32_ppc(struct load_command *lc, struct mach_header *header)
{
	unsigned int			i;
	struct section			*sec;
	struct segment_command	*seg;

	seg = (struct segment_command*)lc;
	sec = (struct section*)\
			(seg + sizeof(struct segment_command*) / sizeof(void*));
	i = 0;
	// check_corrupt_lc_command(lc, header->ncmds, header->sizeofcmds, 32);
	while (i < endian_32(seg->nsects) && endian_32(seg->nsects) != 0)
	{
		if (endian_32(sec->offset) > 0 && endian_32(sec->offset) + endian_32(sec->size) > recover_base()->file_size)
			exit(1);
		if (ft_strcmp(sec->segname, "__TEXT") == 0
			&& ft_strcmp(sec->sectname, "__text") == 0)
		{
			ft_putstr(ft_strjoin(recover_base()->name, "("));
			ft_putstr(ft_strjoin(recover_base()->path_name, ")"));
			ft_putstr(":\nContents of (__TEXT,__text) section\n");
			get_content_ppc(endian_32(sec->addr), endian_32(sec->size), (char *)header + endian_32(sec->offset));
		}
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
		i++;
	}
}

char		*value_ppc(uint32_t n_value, int len)
{
	char	*value_l;
	char	*value_r;
	size_t	value_len;

	value_r = ft_str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(endian_64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	return (padding(value_len, value_l, value_r, len));
}

void	segment_ppc(struct load_command *lc)
{
	struct segment_command	*seg;
	struct section			*sec;
	unsigned int			i;
	t_list					*list_tmp;

	seg = (struct segment_command *)lc;
	sec = (struct section *)(seg + sizeof(seg) / sizeof(void *));
	i = 0;
	if (seg->fileoff > 0 && recover_base()->file_size < endian_32(seg->fileoff) + endian_32(seg->filesize))
	{
		print_err(ERR_CORRUPT);
	}
	if (seg->nsects == 0)
	{
		return ;
	}
	while (i++ < endian_32(seg->nsects))
	{
		list_tmp = (t_list *)malloc(sizeof(t_list));
		list_tmp->content = ft_strdup(sec->sectname);
		ft_lstadd(&recover_base()->list_segment, list_tmp);
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
	}
}


