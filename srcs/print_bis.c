/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 15:59:25 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	print_label(void)
{
	t_base *base;

	base = recover_base();
	if (base->print_name == false && base->archiveNm == false)
		return ;
	ft_putstr("\n");
	ft_putstr(base->name);
	if (base->archiveNm == true)
	{
		ft_putchar('(');
		ft_putstr(base->path_name);
		ft_putchar(')');
	}
	ft_putstr(":\n");
}


void	print_title_archive(void)
{
	t_base	*base;

	base = recover_base();
	ft_putstr("Archive : ");
	ft_putstr(base->name);
	ft_putchar('\n');
}

void	print_label_archive(t_archive *archive)
{
	t_base *base;

	base = recover_base();
	ft_putstr(base->name);
	ft_putchar('(');
	if (!archive->name)
		ft_putstr("unknow");
	else
		ft_putstr(archive->name);
	ft_putstr("):\n");
	ft_putstr("Contents of (__TEXT,__text) section\n");
	return ;
}

void	print_value_archive(t_archive *archive)
{
	if (archive->magicArchive->value && archive->magicArchive->text_section)
	{
		ft_putstr(archive->magicArchive->value);
		ft_putchar('\t');
		ft_putstr(archive->magicArchive->text_section);
		ft_putchar('\n');
	}
}

void	print_value_nm(t_magic *magic)
{
	if (magic->type != 'U')
		ft_putstr(magic->value);
	else if (recover_base()->type_arch == 2)
		ft_putstr("        ");
	else
		ft_putstr("                ");
	ft_putchar(' ');
	ft_putchar(magic->type);
	ft_putchar(' ');
	ft_putstr(magic->name_func);
	ft_putchar('\n');
}
