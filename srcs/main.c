/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 17:01:56 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

int	main(int ac, char **av)
{
	t_base	*base;
	int		i;

	base = recover_base();
	i = 0;
	if (ac >= 2)
	{
		base->nm = ft_strstr(av[0], "ft_nm") != NULL ? true : false;
		base->opt_o = ft_strcmp(av[1], "-o") == 0 && base->nm == true
															? true : false;
		base->print_name = ac == 3 && base->opt_o == false ? true : false;
		i = base->opt_o == true ? i + 1 : i;
		parse_file(base, ac, av, i);
	}
	else
	{
		printf("Nm need argument\n");
		base->err++;
	}
	return (base->err > 1 ? 1 : 0);
}
