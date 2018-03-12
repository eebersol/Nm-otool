/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:44 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		check_in_base(char c, char *base)
{
	int i;
	int feedback;

	feedback = 0;
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == c)
			feedback += 1;
		i++;
	}
	if (c == '-' || c == '+')
		feedback += 1;
	return (feedback);
}

static char		*normalise(char *str, char *base)
{
	long	start;
	long	end;

	start = 0;
	while (0 <= str[start] && str[start] <= 32 && str[start] != '\0')
		start++;
	end = 0;
	while (check_in_base(str[start + end], base))
		end++;
	str[start + end] = '\0';
	return (str + start);
}

static int		convert_number(char nbr, char *base)
{
	int i;

	i = 0;
	while (base[i] != nbr)
		i++;
	return (i);
}

int				ft_atoi_base(char *str, char *base)
{
	int		i;
	long	base_nb;
	long	multiple;
	int		resultat;
	int		signe;

	str = normalise(str, base);
	signe = (str[0] == '-' ? -1 : 1);
	str = (str[0] == '-' || str[0] == '+') ? str + 1 : str;
	base_nb = 0;
	while (base[base_nb] != '\0')
		base_nb++;
	resultat = 0;
	i = 0;
	multiple = 1;
	while (str[i] != '\0')
		i++;
	while (--i >= 0)
	{
		resultat += convert_number(str[i], base) * multiple;
		multiple *= base_nb;
	}
	return (resultat * signe);
}
