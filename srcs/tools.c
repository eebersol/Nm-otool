#include "../includes/nm-otool.h"

static char		read_tab(int i)
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


void	swap_archive(t_archive *node1, t_archive *node2)
{
	t_magic *tempListMagic;
	char	*tempName;

	tempListMagic			= node1->magicArchive;
	tempName 				= node1->name;

	node1->magicArchive 	= node2->magicArchive;
	node1->name 			= node2->name;

	node2->magicArchive 	= tempListMagic;
	node2->name 			= tempName;
}

void sort_alphanumeric_archive(t_archive *node)
{
	int				swapped;
	int 			i;
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
			i = 0;
			if (ft_strcmp(ft_strsub(ptr1->name, 0, ft_strlen(ptr1->next->name)), ptr1->next->name) == 0 
					&& ft_strlen(ptr1->name) > ft_strlen(ptr1->next->name)) {
				swapped = 1;
				swap_archive(ptr1, ptr1->next);
			}
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0) {
				swapped = 1;
				swap_archive(ptr1, ptr1->next);
			}
			// while (ptr1->name[i] && ptr1->next->name[i])
			// {
			// 	if (ptr1->name[i] > ptr1->next->name[i]) {
			// 		swapped = 1;
			// 		swap_archive(ptr1, ptr1->next);
			// 	}
			// 	else if (ptr1->name[i] < ptr1->next->name[i])
			// 		break;
			// 	else
			// 		i++;
			// }
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
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


