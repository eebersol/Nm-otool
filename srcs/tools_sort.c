/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 16:38:49 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	swap(t_magic *node1, t_magic *node2)
{
	char		temp_type;
	char		*temp_value;
	char		*temp_name_func;

	temp_type = node1->type;
	temp_value = node1->value;
	temp_name_func = node1->name_func;
	
	node1->type = node2->type;
	node1->value = node2->value;
	node1->name_func = node2->name_func;
	
	node2->type = temp_type;
	node2->value = temp_value;
	node2->name_func = temp_name_func;
}

void	resort_diff(void)
{
	int			swapped;
	int			i;
	t_magic		*ptr1;
	t_magic		*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = recover_base()->magicBase;
		while (ptr1 && ptr1->next != lptr)
		{
			i = 0;
			if (ft_strcmp(ptr1->name_func, ptr1->next->name_func) == 0
				&& (ptr1->type != 'U' && ptr1->next->type != 'I'))
			{
					swapped = 1;
					swap(ptr1, ptr1->next);
			}
			if (ft_strcmp(ptr1->name_func, ptr1->next->name_func) == 0
				&& (ptr1->type ==  ptr1->next->type + 32))
			{
				//printf("fname : %s - %c\n", ptr1->name_func, ptr1->type);
					swapped = 0;
					swap(ptr1, ptr1->next);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	sort_alphanumeric(t_magic *node)
{
	int			swapped;
	t_magic		*ptr1;
	t_magic		*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = node;
		while (ptr1 && ptr1->next != lptr)
		{
			if (cmp_name(ptr1->name_func, ptr1->next->name_func))
			{
				swapped = 1;
				swap(ptr1, ptr1->next);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	resort_diff();
}

void	swap_archive(t_archive *node1, t_archive *node2)
{
	t_magic	*tem_list_magic;
	char	*temp_name;

	tem_list_magic = node1->magicArchive;
	temp_name = node1->name;
	node1->magicArchive = node2->magicArchive;
	node1->name = node2->name;
	node2->magicArchive = tem_list_magic;
	node2->name = temp_name;
}

void	sort_alphanumeric_archive(t_archive *node)
{
	int				swapped;
	t_archive		*ptr1;
	t_archive		*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = node;
		while (ptr1 && ptr1->next != lptr)
		{
			if (cmp_name(ptr1->name, ptr1->next->name))
			{
				swapped = 1;
				swap_archive(ptr1, ptr1->next);
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
