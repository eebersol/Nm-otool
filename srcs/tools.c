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

void	swap(t_magic *node1, t_magic *node2)
{
	char	tempType;
	char	*tempValue;
	char	*tempNameFunc;

	tempType 			= node1->type;
	tempValue 			= node1->value;
	tempNameFunc 		= node1->name_func;

	node1->type 		= node2->type;
	node1->value 		= node2->value;
	node1->name_func 	= node2->name_func;

	node2->type 		= tempType;
	node2->value 		= tempValue;
	node2->name_func 	= tempNameFunc;
}

void sort_alphanumeric(t_magic *node)
{
	int			swapped;
	int 		i;
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
			i = 0;
			if (ft_strcmp(ft_strsub(ptr1->name_func, 0, ft_strlen(ptr1->next->name_func)), ptr1->next->name_func) == 0 
					&& ft_strlen(ptr1->name_func) > ft_strlen(ptr1->next->name_func)) {
				swapped = 1;
				swap(ptr1, ptr1->next);
			}
			while (ptr1->name_func[i] && ptr1->next->name_func[i])
			{
				if (ptr1->name_func[i] > ptr1->next->name_func[i]) {
					swapped = 1;
					swap(ptr1, ptr1->next);
				}
				else if (ptr1->name_func[i] < ptr1->next->name_func[i])
					break;
				else
					i++;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
