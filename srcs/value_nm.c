/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 13:29:20 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char *padding(int value_len, char *value_l, char *value_r, int len)
{
	int len_br;
	char *body_left;
	char *body_right;
	char *result;

	len_br = 0;
	body_left = (char *)malloc(sizeof(char) * 16);
	if (len == 8 && ft_strlen(value_r) == 8)
		return(value_r);
	if (value_len > len/2+1)
		value_l = ft_strsub(value_l, 0, ft_strlen(value_l) - (ft_strlen(value_l) - (9 - ft_strlen(value_r))));
	else if (value_len < len/2+1)
	{
		value_l = ft_strjoin(value_l, "0");
	 	value_len++;
	}
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	while (len_br + value_len < len)
	{
		body_left = ft_strjoin("0", body_left);
		len_br++;
	}
	body_right 	= ft_strjoin(value_l, value_r);
	result 		= ft_strjoin(body_left, body_right);
	return (result);
}


char		*value(uint64_t n_value)
{
	t_base 	*base;
	char	*value_l;
	char	*value_r;
	size_t	value_len;
	int 	len;

	base = recover_base();
	if (base->type_arch == 2)
		len = 8;
	else
		len = 16;
	value_r = str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	return (padding(value_len, value_l, value_r, len));
}

char		*value_abs(uint64_t n_value)
{
	char 	*value_l;
	int 	value_len;

	value_l = ft_hexa_itoa(n_value);;
	value_len = ft_strlen(value_l);
	while (value_len < 16)
	{
		value_l =  ft_strjoin("0", value_l);
		value_len++;
	}
	return (value_l);
}

char 		*value_manager(t_magic *magic, uint64_t n_value)
{
	if (magic->type == 'A')
		return (value_abs(n_value));
	else
		return (value(n_value));
}
