/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 11:53:40 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

int		lst_count(t_magic *lst)
{
	int		i;
	t_magic	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}

int		lst_count_archive(t_archive *lst)
{
	int			i;
	t_archive	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}

int		lst_count_section(t_section *lst)
{
	int			i;
	t_section	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}

int		lst_count_segment(t_segment *lst)
{
	int			i;
	t_segment	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}

t_magic	*lst_reverse(t_magic *root)
{
	t_magic *new_root;
	t_magic *next;

	new_root = NULL;
	next = NULL;
	while (root)
	{
		next = root->next;
		root->next = new_root;
		new_root = root;
		root = next;
	}
	return (new_root);
}

void	lstdel_at(t_archive **archive, int at)
{
	t_archive	*tmp;
	t_archive	*prev;
	int		count;

	if (!archive || !(*archive))
		return ;
	tmp = *archive;
	prev = NULL;
	count = 0;
	while (count != at && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		count++;
	}
	if (count == at)
	{
		if (prev)
			prev->next = tmp->next;
		else
		{
			*archive = tmp->next;
		}
		// del(tmp->content, tmp->content_size);
		free(tmp);
	}
}

void	remove_doublon(void)
{
	t_base *base;
	t_archive *archive;
	int i;

	base = recover_base();
	i = 0;
	archive = base->archiveBase;
	while (i < lst_count_archive(base->archiveBase))
	{
		if (ft_strcmp(archive->name, archive->next->name) == 0)
		{
			lstdel_at(&base->archiveBase, i);
			remove_doublon();
		}
		i += 2;
		if (archive->next == NULL)
			break ;
		archive = archive->next;
	}
}