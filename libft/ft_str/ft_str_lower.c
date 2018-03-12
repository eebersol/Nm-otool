/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 10:02:34 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:54:06 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_str_lower(char *str)
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
