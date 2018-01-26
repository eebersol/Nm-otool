/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 15:57:00 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

t_base	*recover_base(void)
{
	static t_base	base;

	return (&base);
}

t_base	*init_base(char *name)
{
	t_base	*base;

	base = recover_base();
	base->name = name;
	base->err = false;
	base->archive = false;
	base->index = 1;
	base->magicBase = NULL;
	base->sectionBase = NULL;
	base->nameArchive = NULL;
	base->type_arch = 0;
	return (base);
}
