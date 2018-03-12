/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:34:28 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:46 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	char			*ret;
	unsigned int	i;

	new_str = (char *)malloc(len + 1);
	if (!new_str || !s)
		return (NULL);
	i = start;
	ret = new_str;
	while ((i - start) < len)
	{
		*new_str = s[i];
		new_str++;
		i++;
	}
	*new_str = '\0';
	return (ret);
}
