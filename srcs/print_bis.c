/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 16:14:14 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	print_label(void)
{
	t_base *base;

	base = recover_base();
	if (base->print_name == false)
		return ;
	ft_putstr("\n");
	ft_putstr(base->name);
	ft_putstr(":\n");
}

void	print_label_archive(t_archive *archive)
{
	t_base *base;

	base = recover_base();
	ft_putstr(base->name);
	ft_putchar('(');
	ft_putstr(archive->name);
	ft_putstr("):\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	return ;
}

void	print_value_archive(t_archive *archive)
{
	ft_putstr(archive->magicArchive->value);
	ft_putchar('\t');
	ft_putstr(archive->magicArchive->text_section);
	ft_putchar('\n');
}

void	print_value_nm(t_magic *magic)
{
	if (magic->type != 'U')
		ft_putstr(magic->value);
	else
		ft_putstr("                ");
	ft_putchar(' ');
	ft_putchar(magic->type);
	ft_putchar(' ');
	ft_putstr(magic->name_func);
	ft_putchar('\n');
}
