#include "../includes/nm-otool.h"


static char		secto(t_magic *magic)
{
	t_section 		*tmp;
	t_segment 		*tmpSegment;

	tmp = recover_base()->sectionBase;

	//printf("Len : %d\n", lst_count_section(tmp));
	while (tmp)
	{
		//ft_putstr("while(tmp) -- \n");
		tmpSegment = tmp->seg;
		while (tmpSegment)
		{
		//	ft_putstr("while(tmpSegment) : ");
			// if (tmpSegment->name) {
			// 	ft_putstr(tmpSegment->name);
			// }
			//ft_putstr("NBR : ");
			//ft_putnbr(tmpSegment->nb);
			//ft_putchar('-');
			//ft_putnbr(magic->content->n_sect);
			//ft_putchar('\n');
			if (tmpSegment->name != NULL && tmpSegment->nb == magic->content->n_sect)
			{
				//ft_putstr("ENTER : ");
				//ft_putstr(tmpSegment->name);
				//ft_putchar('\n');
				if (!ft_strcmp(tmpSegment->name, SECT_DATA))
					return ('D');
				else if (!ft_strcmp(tmpSegment->name, SECT_BSS))
					return ('B');
				else if (!ft_strcmp(tmpSegment->name, SECT_TEXT))
					return ('T');
				else
					return ('S');
			}
			if (tmpSegment->next == NULL)
				break;
			tmpSegment = tmpSegment->next;
		}
		if (tmp->next == NULL)
				break;
		tmp = tmp->next;
	}
	//ft_putstr("nothing found \n");
	return ('S');
}

char get_type(uint8_t n_type, t_magic *magic)
{
	char c;

	(void)magic;
	(void)n_type;
//	ft_putstr(magic->name_func);
//	ft_putchar('\n');
	c = 0;
	if ((n_type & N_TYPE) == N_EXT)
		printf("get_type : EXT\n");
	else if ((n_type & N_TYPE) == N_LSYM ||(n_type & N_TYPE) ==  N_BINCL)
		printf("get_type : LOCAL\n");
	else if ((n_type & N_TYPE) == N_UNDF) {
//		printf("get_type : N_UNDF\n");
		c = 'U';
	}
	else if ((n_type & N_TYPE) == N_ABS)
	{
//		printf("get_type : N_ABS\n");
		c = 'A';
	}
	else if ((n_type & N_TYPE) == N_SECT)
	{
//		printf("get_type : N_SECT\n");
		c = secto(magic);
	}
	else if ((n_type & N_TYPE) == N_PBUD)
	{
//		printf("get_type : N_PBUD\n");
		c = 's';
	}
	else if ((n_type & N_TYPE) == N_INDR)
		printf("get_type : N_INDR\n");
	if ((n_type & N_EXT) == 0 && c != '?')
		c += 32;
//	printf("get_type :  return value : %c\n", c);
	// if (n_type == 15 || n_type == 31) 
	// {
	// 	if (magic->content->n_sect == 11)
	// 		return ('D');
	// 	else if (magic->content->n_sect == 3 || magic->content->n_sect == 4 || magic->content->n_sect == 5 || magic->content->n_sect == 7 || magic->content->n_sect == 10 || magic->content->n_sect == 12)
	// 		return ('S');
	// 	else
	// 		return ('T');
	// }
	// else if (n_type == 30 && magic->content->n_sect == 2)
	// 	return ('s');
	// else if (n_type == N_EXT)
	// 	return ('U');
	// else if (n_type == N_STAB || n_type == N_PEXT) {
	// 	printf("FIND :: N_STAB -- N_EXT\n");
	// 	return('X');
	// }
	// else if (n_type == N_TYPE || n_type == 30) 
	// {
	// 	if ((n_type & N_TYPE) == N_UNDF)
	// 		printf("N_UNDF\n");
	// 	else if ((n_type & N_TYPE) == N_ABS)
	// 		printf("N_ABS\n");
	// 	else if ((n_type & N_TYPE) == N_PBUD)
	// 		printf("N_PBUD\n");
	// 	else if ((n_type & N_TYPE) == N_INDR)
	// 		printf("N_INDR\n");
	// 	else if ((n_type & N_TYPE) == N_SECT)
	// 	{
	// 		if (magic->content->n_sect == 1)
	// 			return ('t');
	// 		else if ((magic->content->n_sect == 4 || magic->content->n_sect == 10) && ft_strstr(magic->name_func, "."))
	// 			return ('b');
	// 		else if (magic->content->n_sect == 2 || magic->content->n_sect == 3 || magic->content->n_sect == 4 || magic->content->n_sect == 5 || magic->content->n_sect == 9  || magic->content->n_sect == 10|| magic->content->n_sect == 12)
	// 			return ('s');
	// 		else if (magic->content->n_sect == 11)
	// 			return ('d');
	// 	}
	// 	return ('b');
	// }
	// else {
		// ft_putstr("No type found.");
	//ft_putstr("return type : ");
	//ft_putchar(c);
	//ft_putchar('\n');
		return (c);
	// }
}

char 	*get_value(uint64_t n_value, t_magic *magic)
{
	char 	*value_l;
	char 	*value_r;
	size_t 	value_len;
	size_t 	i;
	int 	padding;


	(void)magic;
	value_r = ft_itoa_base(n_value, 16);
	i = 0;
	while (i < ft_strlen(value_r)) {
		value_r[i] = ft_tolower(value_r[i]);
		i++;
	}
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	if (value_len < 9)
	{
		while (value_len < 9)
		{
			value_l = ft_strjoin(value_l, "0");
			value_len = ft_strlen(value_l) + ft_strlen(value_r);
		}
	}
	else if (value_len > 9)
	{
		padding = 9 - ft_strlen(value_r);
		value_l = ft_strsub(value_l, 0, padding);
		value_len = ft_strlen(value_l) + ft_strlen(value_r);
	}
	value_l = ft_strjoin("0000000", value_l);
	return (ft_strjoin(value_l, value_r));
}
