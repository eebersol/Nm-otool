/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 11:24:10 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"


void debug(void)
{
	t_base *base;
	t_magic *magic;

	base = recover_base();
	magic = base->magicBase;
	while (magic)
	{
		printf("\nname : %s\n", magic->name_func);
		printf("value : %s\n", magic->value);
		if (magic->next == NULL)
			break ;
		magic = magic->next;
	}

}