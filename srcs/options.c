/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/20 16:37:46 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

static void		choose_option(t_base *base, char option)
{
	if (option == 'o')
		base->opt->o = true;
	else if (option == 'g')
		base->opt->g = true;
	else if (option == 'j')
		base->opt->j = true;
	else if (option == 'U')
		base->opt->uu = true;
	else if (option == 'u')
		base->opt->u = true;
	else
		base->opt->wrg_opt = 0;
}

void			option(char *options, int ac)
{
	t_base *base;
	size_t i;

	(void)ac;
	base = recover_base();
	base->opt = (t_option_nm*)malloc(sizeof(t_option_nm));
	base->opt->wrg_opt = 1;
	i = 0;
	if (options && options[0] == '-')
	{
		while (++i < ft_strlen(options))
			choose_option(base, options[i]);
		if (base->opt->wrg_opt == 0)
			print_err(ERR_OPT);
	}
	else
		base->opt->wrg_opt = 2;
	return ;
}
