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

	if ((n_type & N_TYPE) == N_LSYM ||(n_type & N_TYPE) ==  N_BINCL)
		c = 'X';
	else if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT)
		c = secto(magic);
	else if ((n_type & N_TYPE) == N_PBUD)
		c = 's';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else
		c = 'X';
	if ((n_type & N_EXT) == 0 && c != 'X')
		c += 32;
	//printf("RETURN |%c|\n", c);
	return (c);
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
