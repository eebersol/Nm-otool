/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/02/22 13:02:50 by eebersol         ###   ########.fr       */
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
	t_list	*list;
	t_magic	*magic;

	list = (t_list *)malloc(sizeof(t_list));
	magic = (t_magic *)malloc(sizeof(t_magic));
	magic->text_section = (char*)malloc(sizeof(char*) * ft_strlen(str) + 1);
	magic->text_section = str;
	magic->value = test_addr;
	list->content = magic;
	ft_lstaddend(&recover_base()->list_magic, list);
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
		magic = (t_magic *)tmp->content;
		if (ft_strcmp(node->name_func, magic->name_func) == 0
			&& magic->type == 'I')
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		if (ft_strcmp(node->name_func, magic->name_func) == 0
			&& node->type < magic->type && node->type + 32 == magic->type)
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		if (ft_strcmp(node->name_func, magic->name_func) < 0)
			return (ft_lstadd_at(&base->list_magic, complet_node, j));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
		j++;
	}
	ft_lstaddend(&base->list_magic, complet_node);
}

void		find_best_place(t_base *base, t_list *tmp)
{
	t_magic	*tmp_magic;
	char	*to_place;
	char	*curr;

	tmp_magic = (t_magic*)tmp->content;
	if (ft_lstcount(base->list_magic) == 0)
		return (ft_lstadd(&base->list_magic, tmp));
	else if (ft_lstcount(base->list_magic) == 1)
	{
		to_place = (char*)((t_magic*)tmp->content)->name_func;
		curr = (char*)((t_magic*)base->list_magic->content)->name_func;
		if (ft_strcmp(curr, to_place) > 0)
			return (ft_lstadd(&base->list_magic, tmp));
		else
			return (ft_lstaddend(&base->list_magic, tmp));
	}
	else
		find_place(tmp, tmp_magic);
}
