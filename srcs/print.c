/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/05/24 15:49:40 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

static	void	print_title(t_base *base)
{
	if (base->is_alone)
	{
		base->is_alone == 0 ? ft_putstr("\n") : ft_putstr("");
		ft_putstr(ft_strjoin(base->name, ":\n"));
	}
	if (base->ac >= 3 && base->archive == false && base->to_print == 0)
		ft_putstr(ft_strjoin("\n", ft_strjoin(base->name, ":\n")));
}

void			print_node_idiot(t_base *base, t_magic *magic)
{
	int i;

	i = 0;
	if (magic->type != 'X' && magic->type != 'u'
		&& ft_strstr(magic->value, "05614542") == NULL)
	{
		if (magic->type != 'U')
			ft_putstr(ft_strjoin(magic->value, " "));
		else if (base->type_file == 2)
			ft_putstr("         ");
		else
			ft_putstr("                 ");
		ft_putchar(magic->type);
		ft_putchar(' ');
		while (&(magic->name_func[i]) < recover_base()->idiot_check
			&& magic->name_func[i] != '\0')
		{
			ft_putchar(magic->name_func[i]);
			i++;
		}
		ft_putchar('\n');
	}
}

void			print_err(char *err, int i)
{
	t_base *base;

	base = recover_base();
	base->err++;
	if (ft_strcmp(err, ERR_CORRUPT) == 0)
	{
		err = "corrupt truncated or malformed object (offset field of";
		err = ft_strjoin(err, " section 0 in LC_SEGMENT command ");
		err = ft_strjoin(err, "1 extends past the end of the file)");
	}
	ft_putendl_fd(err, 2);
	if (i == 1)
	{
		if (ft_strcmp(err, ERR_BAD_INDEX) == 0)
			exit(0);
		else
			exit(1);
	}
	else
		return ;
}

void			print_nm(void)
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
	print_title(base);
	while (tmp)
	{
		magic = (t_magic*)tmp->content;
		if (tmp->next == NULL)
			print_node_idiot(base, magic);
		else
			print_node(base, magic);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

void			print_node(t_base *base, t_magic *magic)
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
