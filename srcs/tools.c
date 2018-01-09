#include "../includes/nm-otool.h"

void	*smap(size_t len)
{
	return (mmap(NULL, len, FLAG_PROT, FLAG_MAP, -1, 0));
}

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

void pairWiseSwap(t_magic *node)
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
