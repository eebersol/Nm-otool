/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 11:01:55 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

t_base	*recover_base(void)
{
	static t_base	base;

	return (&base);
}

t_base	*init_base(char *name)
{
	t_base	*base;

	base = recover_base();
	base->archive = false;
	base->ac = 0;
	base->strsize = 0;
	base->file_size = 0;
	base->power_pc = false;
	base->ii = false;
	base->type_file = 0;
	base->name = name;
	base->path_name = NULL;
	base->err = false;
	base->is_alone = false;
	base->print_or = false;
	base->list_magic = NULL;
	base->list_segment = NULL;
	base->to_print = 0;
	return (base);
}

t_base	*reinit_base(char *name)
{
	t_base	*base;

	base = recover_base();
	base->type_file = 0;
	base->name = name;
	base->list_magic = NULL;
	base->list_segment = NULL;
	return (base);
}
