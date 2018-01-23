/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 18:16:42 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char		get_char_32(t_segment *segment, t_magic *magic)
{
	t_segment	*tmp_segment;

	tmp_segment = segment;
	while (tmp_segment)
	{
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content_32->n_sect)
		{
			if (!ft_strcmp(tmp_segment->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp_segment->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		if (tmp_segment->next == NULL)
			break ;
		tmp_segment = tmp_segment->next;
	}
	return ('X');
}

char		get_char(t_segment *segment, t_magic *magic)
{
	t_segment	*tmp_segment;

	tmp_segment = segment;
	while (tmp_segment)
	{
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content->n_sect)
		{
			if (!ft_strcmp(tmp_segment->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp_segment->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		if (tmp_segment->next == NULL)
			break ;
		tmp_segment = tmp_segment->next;
	}
	return ('X');
}

char		get_type(uint8_t n_type, t_magic *magic)
{
	char c;

	(void)magic;
	(void)n_type;
	if ((n_type & N_TYPE) == N_LSYM || (n_type & N_TYPE) == N_BINCL)
		c = 'X';
	else if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT && recover_base()->type_arch != 2)
		c = browse_section(magic);
	else if ((n_type & N_TYPE) == N_SECT && recover_base()->type_arch == 2)
		c = browse_section_32(magic);
	else if ((n_type & N_TYPE) == N_PBUD)
		c = 's';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else
		c = 'X';
	if ((n_type & N_EXT) == 0 && c != 'X')
		c += 32;
	return (c);
}

char		*get_value(uint64_t n_value)
{
	char	*value_l;
	char	*value_r;
	size_t	value_len;
	size_t	i;
	int		padding;

	i = 0;
	value_r = str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	if (value_len < 9)
	{
		while (value_len < 9)
		{
			value_l = ft_strjoin(value_l, "0");
			value_len = ft_strlen(value_l) + ft_strlen(value_r);
		}
	}
	else if (value_len > 9)
	{
		padding = 9 - ft_strlen(value_r);
		value_l = ft_strsub(value_l, 0, padding);
		value_len = ft_strlen(value_l) + ft_strlen(value_r);
	}
	return (ft_strjoin(ft_strjoin("0000000", value_l), value_r));
}
