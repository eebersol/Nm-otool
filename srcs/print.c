/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 12:38:23 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void	print_err(char *err)
{
	t_base *base;

	base = recover_base();
	base->err++;
	if (ft_strcmp(err, ERR_CORRUPT) == 0)
	{
		err = "corrupt truncated or malformed object (offset field of";
		err = ft_strjoin(err, "section 0 in LC_SEGMENT command ");
		err = ft_strjoin(err, "1 extends past the end of the file)\n");
	}
	ft_putstr(err);
}

void	print_otool(void)
{
	t_base	*base;
	t_list	*list;
	t_magic	*magic_tmp;

	base = recover_base();
	list = base->list_magic;
	while (list)
	{
		magic_tmp = (t_magic*)list->content;
		if (magic_tmp->value && magic_tmp->text_section)
		{
			ft_putstr(magic_tmp->value);
			ft_putchar('\t');
			ft_putstr(magic_tmp->text_section);
			ft_putchar('\n');
		}
		if (list->next == NULL)
			break ;
		list = list->next;
	}
}

void	print_nm(void)
{
	t_list	*tmp;
	t_magic	*magic;
	t_base	*base;

	base = recover_base();
	tmp = base->list_magic;
	if (base->archive == true)
	{
		ft_putstr(ft_strjoin("\n", base->name));
		ft_putstr(ft_strjoin("(", base->path_name));
		ft_putstr("):\n");
	}
	if (base->is_alone)
	{
		base->is_alone == 0 ? ft_putstr("\n") : ft_putstr("");
		ft_putstr(ft_strjoin(base->name, ":\n"));
	}
	while (tmp)
	{
		magic = (t_magic*)tmp->content;
		print_node(base, magic);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

void	print_node(t_base *base, t_magic *magic)
{
	if (ft_strlen(magic->name_func) > 0 && magic->type != 'X'
		&& ft_strstr(magic->name_func, "radr://") == NULL
			&& magic->type != 'u')
	{
		if (magic->type != 'U')
			ft_putstr(ft_strjoin(magic->value, " "));
		else if (base->type_file == 2)
			ft_putstr("         ");
		else
			ft_putstr("                 ");
		ft_putchar(magic->type);
		ft_putchar(' ');
		ft_putstr(ft_strjoin(magic->name_func, "\n"));
	}
}
