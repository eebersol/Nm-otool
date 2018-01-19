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
	int		i;
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
	int		i;
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