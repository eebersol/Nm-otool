#include "../includes/nm-otool.h"

static void	 find_something(t_magic *magic)
{
	(void)magic;
	//printf("Find something : %u -- ", magic->content->n_sect);
}

char get_type(uint8_t n_type, t_magic *magic)
{
//	n_type = ft_itoa(n_type);

	if (n_type == 15 || n_type == 31) 
	{
		if (magic->content->n_sect == 11)
				return ('D');
		if (magic->content->n_sect == 12)
				return ('S');
		return ('T');
	}
	else if (n_type == N_STAB) {
		return('X');
	}
	else if (n_type == N_PEXT) {
		return ('X');
	}
	else if (n_type == N_TYPE) {

	//	printf("\nname : %s - ", magic->name_func);

		if ((n_type & N_TYPE) == N_UNDF)
			printf("N_UNDF\n");
		else if ((n_type & N_TYPE) == N_ABS)
			printf("N_ABS\n");
		else if ((n_type & N_TYPE) == N_SECT)
		{
			if (magic->content->n_sect == 1)
				return ('t');
			else if (magic->content->n_sect == 5 || magic->content->n_sect == 4)
				return ('s');
			else if (magic->content->n_sect == 11)
				return ('d');
			find_something(magic);
			//printf("N_SECT\n");
		}
		else if ((n_type & N_TYPE) == N_PBUD)
			printf("N_PBUD\n");
		else if ((n_type & N_TYPE) == N_INDR)
			printf("N_INDR\n");
		return ('b');
	}
	else if (n_type == N_EXT)
		return ('U');
	else {
		// ft_putstr("No type found.");
		return ('X');
	}
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
	//value_l = ft_strsub(value_l, 0, ft_strlen(value_l)-1);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	// if (ft_strcmp(magic->name_func, "_boolean_check") == 0) {
	// 		printf("n_sect - > %s\n", magic->name_func);
	// 		printf(" %s - %zu/16 -- %s - %zu/16\n", value_l, ft_strlen(value_l), value_r, ft_strlen(value_r));
	// 		printf("value_len : %zu [%s]\n", value_len, ft_strjoin(value_l, value_r));
	// 	}
	if (value_len < 9)
	{
	//	printf("1\n");
		while (value_len < 9)
		{
			value_l = ft_strjoin(value_l, "0");
			value_len = ft_strlen(value_l) + ft_strlen(value_r);
		}
	}
	else if (value_len > 9)
	{
	//	printf("2 remove %zu char\n", 9 - ft_strlen(value_l));
		padding = 9 - ft_strlen(value_r);
		value_l = ft_strsub(value_l, 0, padding);
		value_len = ft_strlen(value_l) + ft_strlen(value_r);
	}
	// if (ft_strcmp(magic->name_func, "_boolean_check") == 0) {
	// 		printf("value_len : %zu [%s]\n", value_len, ft_strjoin(value_l, value_r));
	// }
	value_l = ft_strjoin("0000000", value_l);
	return (ft_strjoin(value_l, value_r));

}
// char 	*get_value(uint64_t n_value, char type)
// {	
// 	char 	*value;
// 	char 	*body;
// 	size_t 	len;
// 	size_t 	i;

// 	value 	= ft_itoa_base(n_value, 16);
// 	len 	= 16 - ft_strlen(value);
// 	body 	= (char*)malloc(sizeof(char) * len);
// 	i 		= 0;
// 	while (i < ft_strlen(value)) {
// 		value[i] = ft_tolower(value[i]);
// 		i++;
// 	}
// 	value[i] = '\0';
// 	i 		= 0;
// 	while (i < len) {
// 		if (i == 7 && (type == 'T' || type == 't' || type == 'b' || type == 'd' || type == 'D' || type == 's'))
// 			body[i] = '1';
// 		else
// 			body[i] = '0';
// 		i++;
// 	}
// 	body[i] = '\0';
// 	value = ft_strjoin(body, value);
// 	if (type == 'T' || type == 't' || type == 'b' || type == 'd' || type == 'D' || type == 's') {
// 		return (value);
// 	}
// 	else {
// 		return ("                ");
// 	}
// }