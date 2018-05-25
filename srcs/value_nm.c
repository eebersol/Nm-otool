/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/13 12:21:21 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

char		*padding(int value_len, char *value_l, char *value_r, int len)
{
	char	*body_left;
	char	*body_right;
	char	*result;

	body_left = "0000000000000000";
	if (len == 8 && ft_strlen(value_r) == 8)
		return (value_r);
	if (value_len > len / 2 + 1)
	{
		value_l = ft_strsub(value_l, 0, ft_strlen(value_l)
			- (ft_strlen(value_l) - (9 - ft_strlen(value_r))));
	}
	else if (value_len < len / 2 + 1)
	{
		value_l = ft_strjoin(value_l, "0");
		value_len++;
	}
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	body_left = ft_strsub(body_left, 0, len - value_len);
	body_right = ft_strjoin(value_l, value_r);
	result = ft_strjoin(body_left, body_right);
	return (result);
}

char		*value(uint64_t n_value, int len)
{
	char	*value_l;
	char	*value_r;
	size_t	value_len;

	value_r = ft_str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(endian_64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	return (padding(value_len, value_l, value_r, len));
}

char		*value_abs(uint64_t n_value, int len)
{
	char	*value_l;
	int		value_len;

	value_l = ft_hexa_itoa(n_value);
	value_len = ft_strlen(value_l);
	while (value_len < len)
	{
		value_l = ft_strjoin("0", value_l);
		value_len++;
	}
	return (value_l);
}

char		*value_manager(char type, uint64_t n_value)
{
	t_base	*base;
	int		len;
	char	*result;

	base = recover_base();
	len = base->type_file == 2 ? 8 : 16;
	if (type == 'A')
		result = value_abs(n_value, len);
	else
		result = value(n_value, len);
	return (result);
}
