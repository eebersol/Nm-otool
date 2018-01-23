/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 13:54:15 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char	*str_lower(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (NULL);
	while (i < ft_strlen(str))
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char	read_tab(int i)
{
	char	*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

char	*itoa_base(int val, int base, int output_size)
{
	char			buffer[output_size + 1];
	char			*p;
	unsigned int	unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

t_magic	*add_list(t_magic *magic, char *str, char *test_addr, int flag)
{
	magic->text_section = (char*)malloc(sizeof(char*) * ft_strlen(str) + 1);
	magic->text_section = str;
	magic->value = test_addr;
	if (flag == 0 )
	{
		magic->next = (t_magic*)malloc(sizeof(t_magic));
		magic = magic->next;
	}
	else
		magic->next = NULL;
	return (magic);
}

int		cmp_name(char *str1, char *str2)
{
	if (ft_strcmp(ft_strsub(str1, 0,
		ft_strlen(str2)), str2) == 0
			&& ft_strlen(str1) > ft_strlen(str2))
		return (1);
	else if ((ft_strcmp(str1, str2) > 0))
		return (1);
	else
		return (0);
}
