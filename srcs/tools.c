/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/13 12:22:30 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

static char	read_tab(int i)
{
	char	*tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

char		*itoa_base(int val, int base, int output_size)
{
	char			buffer[output_size + 1];
	char			*p;
	unsigned int	unsigned_val;

	unsigned_val = (unsigned int)val;
	if (base > 36 || base < 2)
		return (NULL);
	buffer[output_size] = 0;
	p = buffer + output_size - 1;
	*p = '0';
	if (unsigned_val > 0)
	{
		while (unsigned_val > 0)
		{
			*p-- = read_tab(unsigned_val % base);
			unsigned_val = unsigned_val / base;
			if (p < buffer)
				break ;
		}
		p++;
	}
	while (p > buffer)
		*--p = '0';
	return (ft_strdup(p));
}

void		add_list(char *str, char *test_addr)
{
	ft_putstr(test_addr);
	ft_putchar('\t');
	ft_putstr(str);
	ft_putchar('\n');
}

void		find_place(t_list *complet_node, t_magic *node)
{
	t_base	*base;
	t_list	*tmp;
	t_magic	*magic;
	int		j;

	j = 0;
	base = recover_base();
	tmp = base->list_magic;
	while (tmp)
	{
		magic = tmp->content;
		complet_node->next = NULL;
		if (ft_strcmp(node->name_func, magic->name_func) == 0
			&& magic->type == 'I')
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		if (ft_strcmp(node->name_func, magic->name_func) == 0
			&& node->type < magic->type && node->type + 32 == magic->type)
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		if (ft_strcmp(node->name_func, magic->name_func) < 0)
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		tmp = tmp->next;
		j++;
	}
	ft_lstaddend(&base->list_magic, complet_node);
}

void		find_best_place(t_base *base, t_list *tmp, int i)
{
	char	*to_place;
	char	*curr;

	if (i == 0)
	{
		ft_lstadd(&base->list_magic, tmp);
		base->list_magic->next = NULL;
	}
	else if (i == 1)
	{
		to_place = (char*)((t_magic*)tmp->content)->name_func;
		curr = (char*)((t_magic*)base->list_magic->content)->name_func;
		if (ft_strcmp(curr, to_place) > 0)
			return (ft_lstadd(&base->list_magic, tmp));
		else
		{
			tmp->next = NULL;
			return (ft_lstaddend(&base->list_magic, tmp));
		}
	}
	else
		find_place(tmp, (t_magic*)tmp->content);
}
