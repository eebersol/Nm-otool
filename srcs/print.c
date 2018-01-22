/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/22 16:14:37 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	print_manager(void)
{
	t_base	*base;

	base = recover_base();
	if (base->nm == true)
		print_nm();
	else if (base->archive == true)
		add_archive();
	else if (base->nm == false && base->archive == false)
		print_otool();
}

void	print_err(char *err)
{
	t_base *base;

	base = recover_base();
	base->err++;
	ft_putstr("nm: ");
	ft_putstr(err);
}

void	print_nm(void)
{
	t_magic	*magic;

	magic = recover_base()->magicBase;
	sort_alphanumeric(magic);
	resort_diff();
	print_label();
	while (magic)
	{
		if (magic->type != 'X' && magic->name_func
			&& ft_strlen(magic->name_func) > 0
				&& ft_strstr(magic->name_func, "radr:") == NULL
					&& magic->type != 'u')
			print_value_nm(magic);
		if (magic->next == NULL)
			break ;
		magic = magic->next;
	}
}

void	print_otool(void)
{
	t_base	*base;
	t_magic	*magic_tmp;

	base = recover_base();
	magic_tmp = base->magicBase;
	while (magic_tmp)
	{
		ft_putstr(magic_tmp->value);
		ft_putchar('\t');
		ft_putstr(magic_tmp->text_section);
		ft_putchar('\n');
		if (magic_tmp->next == NULL)
			break ;
		magic_tmp = magic_tmp->next;
	}
}

void	print_archive(void)
{
	t_archive	*archive;

	archive = recover_base()->archiveBase;
	if (recover_base()->archive == false)
		return ;
	sort_alphanumeric_archive(archive);
	while (archive)
	{
		print_label_archive(archive);
		if (archive->magicArchive)
		{
			while (archive->magicArchive)
			{
				print_value_archive(archive);
				if (archive->magicArchive->next == NULL)
					break ;
				archive->magicArchive = archive->magicArchive->next;
			}
		}
		if (archive->next == NULL)
			break ;
		archive = archive->next;
	}
}
