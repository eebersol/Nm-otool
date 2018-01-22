/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 15:25:43 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

int	main(int ac, char **av)
{
	t_base	*base;

	base = recover_base();
	if (ac >= 2)
	{
		base->print_name = ac == 3 ? true : false;
		base->nm = ft_strstr(av[0], "ft_nm") != NULL ? true : false;
		parse_file(base, ac, av);
	}
	else
	{
		printf("Nm need argument\n");
		base->err++;
	}
	return (base->err > 1 ? 1 : 0);
}
