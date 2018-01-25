/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/25 16:29:03 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

//TRUE
// 0000000100000000 T __mh_execute_header
// 0000000100000f73 T _main
// 0000000100000f73
// 0000001000000f73
// 0000001000000f730
// 0000001000000f73
//        1000000f73
// 0000000100001018 S _shim_marker
//                  U _xcselect_invoke_xcrun
//                  U dyld_stub_binder

// FALSE
// 0000000100000000 T __mh_execute_header
// 0000000100000000 T __mh_execute_header
// 0000000 100000f73
// 000000 1000000 f73 T _main
// 0000010000001018 S _shim_marker
//                  U _xcselect_invoke_xcrun
//                  U dyld_stub_binder



static char *padding(int value_len, char *value_l, char *value_r, int len)
{
	int padding;
	int len_br;
	char *body_left;
	char *body_right;
	char *result;

	len_br = 0;
	body_left = (char *)malloc(sizeof(char) * 16);	
//	printf("\n\nvalue_l : %s\nvalue_r : %s\n len : %d\nvalue_len : %d\n", value_l, value_r, len, value_len);



	if (len == 8 && ft_strlen(value_r) == 8)
		return(value_r);
	if (value_len > len/2+1)
	{
		padding = ft_strlen(value_l) - (ft_strlen(value_l) - (len/2+1 - ft_strlen(value_r)));
	//	printf("Avant : %s - %d\n", value_l, padding);
		value_l = ft_strsub(value_l, 0, ft_strlen(value_l) - (ft_strlen(value_l) - (9 - ft_strlen(value_r))));
	//	printf("Apres : %s\n", value_l);
	}
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
	// printf("while (%d + %d < %d)\n", value_len, len_br, len);
	// if (value_len > len/2)
	// {
	// 	padding = ft_strlen(value_l) - (9 + ft_strlen(value_r) - 16);
	// 	printf("value_l avant : %s -- %d\n", value_l, padding);
	// 	value_l = ft_strsub(value_l, 0, padding);
	// 	printf("value_l apres : %s  -- %d\n", value_l, padding);
	// }
	// value_len = ft_strlen(value_l) + ft_strlen(value_r);
	// printf("value_len %d\n", value_len);
	// printf("%zu -- %s\n", ft_strlen(value_l), value_l);
	// while (value_len < len/2+1)
	// {
	// 	value_r = ft_strjoin(value_r, "0");
	// 	value_len++;
	// }
	// while (len_br > 0)
	// {
	// 	body_left = ft_strjoin("0", body_left);
	// 	len_br--;
	// }
//	printf("body left : %s\n", body_left);
	// while (value_len + len_br < len)
	// {
	// 	body_left = ft_strjoin("0", body_left);
	// 	len_br++;
	// }
	// while (value_len > len/2)
	// {
	// 	padding = len - ft_strlen(value_r);	
	// }
	// if (value_len < len)
	// {
	// 	printf("1\n");
	// 	while (value_len < len)
	// 	{
	// 		body_left = ft_strjoin("0", body_left);
	// 		value_len++;
	// 	}
	// }
	// else if (value_len > len/2)
	// {
	// 	printf("2\n");
	// 	padding = len - ft_strlen(value_r);
	// 	value_l = ft_strsub(value_l, 0, padding);
	// 	value_len--;
	// }
	body_right 	= ft_strjoin(value_l, value_r);
	result 		= ft_strjoin(body_left, body_right);
	return (result);
}

char		*get_value(uint64_t n_value, t_magic *magic)
{
	t_base 	*base;
	char	*value_l;
	char	*value_r;
	size_t	value_len;
	int 	len;

	(void)magic;
	base = recover_base();
	if (base->is_32_dylib == true)
		len = 8;
	else
		len = 16;
	value_r = str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	// if (ft_strcmp(magic->name_func, "_File") == 0)
	// {
	// 	printf("value_l : %s\n", value_l);
	// 	printf("value_r : %s\n", value_r);
	// 	printf("ICI %zu\n", value_len);
	// }
	return (padding(value_len, value_l, value_r, len));
}

char		*get_value_abs(uint64_t n_value, t_magic *magic)
{
	char 	*value_l;
	char 	*value_r;
	int 	value_len;
	char *result;

	(void)magic;
	value_l = ft_hexa_itoa(n_value);
	value_r = "";
	value_len = ft_strlen(value_l);
	result = "";
	// if (ft_strcmp(magic->name_func, "_File") == 0)
	// 	printf("ICI %d -- %s\n", value_len, value_l);
	while (value_len < 16)
	{
		result =  ft_strjoin(result, "0");
		value_len++;
	}
	result = ft_strjoin(result, value_l);
	return (result);
}

char 		*get_value_manager(t_magic *magic, uint64_t n_value)
{
	char *result;

	// if (ft_strcmp(magic->name_func, "_File") == 0)
	// {
	// 	printf("LA\n");
	// }
	if (magic->type == 'A')
		result = get_value_abs(n_value, magic);
	else
		result = get_value(n_value, magic);
//	if (ft_strcmp(magic->name_func, "_File") == 0)
	// {
	// 	printf("LA %s\n", result);
	// }
	return (result);
}
