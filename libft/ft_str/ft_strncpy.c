/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:09:40 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;
	char			*ret;

	ret = dest;
	i = 0;
	while (*src && i < n)
	{
		*dest = *src;
		i++;
		dest++;
		src++;
	}
	while (i < n)
	{
		*dest = '\0';
		dest++;
		i++;
	}
	return (ret);
}
