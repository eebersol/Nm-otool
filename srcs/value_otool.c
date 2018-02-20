/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/20 16:51:00 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

char		*get_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

int			get_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	if (word == NULL)
		return (-1);
	x = ft_atoi(word);
	return (x);
}

char		*get_value_otool_archive(uint64_t n_value)
{
	char	*value_l;
	char	*value_r;
	size_t	value_len;
	int		padding;

	value_r = ft_str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	if (value_len < 9)
	{
		while (value_len < 9)
		{
			value_l = ft_strjoin("0", value_l);
			value_len = ft_strlen(value_l) + ft_strlen(value_r);
		}
	}
	else if (value_len > 9)
	{
		padding = 9 - ft_strlen(value_r);
		value_l = ft_strsub(value_l, 0, padding);
		value_len = ft_strlen(value_l) + ft_strlen(value_r);
	}
	value_l = ft_strjoin(ft_strjoin("0000000", value_l), value_r);
	value_l = ft_strjoin("0", ft_strsub(value_l, 0, ft_strlen(value_l) - 1));
	return (value_l);
}

char		*get_value_otool_exec(uint64_t n_value)
{
	char	*value_l;
	char	*value_r;
	size_t	value_len;
	int		padding;

	value_l = ft_itoa_base(n_value, 16);
	value_l = ft_strsub(value_l, 0, ft_strlen(value_l) - 1);
	value_r = ft_str_lower(ft_itoa_base(swap_uint64(n_value), 16));
	if (ft_strlen("0000000") + ft_strlen(value_l) + ft_strlen(value_r) < 16)
	{
		value_len = ft_strlen("0000000")
			+ ft_strlen(value_l) + ft_strlen(value_r);
		while (value_len < 16)
		{
			value_l = ft_strjoin(value_l, "0");
			value_len++;
		}
	}
	else if (ft_strlen("0000000")
		+ ft_strlen(value_l) + ft_strlen(value_r) > 16)
	{
		padding = 16 - (ft_strlen(value_r) + ft_strlen("0000000"));
		value_l = ft_strsub(value_l, 0, padding);
	}
	return (ft_strjoin("0000000", ft_strjoin(value_l, value_r)));
}

char		*val_otool(uint64_t n_value)
{
	t_base	*base;
	char	*ret;

	base = recover_base();
	ret = NULL;
	if (base->archive == true)
		ret = get_value_otool_archive(n_value);
	else
		ret = get_value_otool_exec(n_value);
	if (recover_base()->type_file == 2)
		ret = ft_strsub(ret, ft_strlen(ret) / 2, ft_strlen(ret));
	return (ret);
}
