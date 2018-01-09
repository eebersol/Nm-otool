#include "../includes/nm-otool.h"


char get_type(uint8_t n_type)
{
//	n_type = ft_itoa(n_type);

	if (n_type == 15 || n_type == 31) {
		return ('T');
	}
	else if (n_type == N_STAB) {
		return('X');
	}
	else if (n_type == N_PEXT) {
		return ('X');
	}
	else if (n_type == N_TYPE) {
		return ('b');
	}
	else if (n_type == N_EXT)
		return ('U');
	else {
		// ft_putstr("No type found.");
		return ('X');
	}
}

char 	*get_value(uint64_t n_value, char type)
{	
	char 	*value;
	char 	*body;
	size_t 	len;
	size_t 	i;

	value 	= ft_itoa_base(n_value, 16);
	len 	= 16 - ft_strlen(value);
	body 	= (char*)malloc(sizeof(char) * len);
	i 		= 0;
	while (i < ft_strlen(value)) {
		value[i] = ft_tolower(value[i]);
		i++;
	}
	value[i] = '\0';
	i 		= 0;
	while (i < len) {
		body[i] = '0';
		i++;
	}
	body[i] = '\0';
	value = ft_strjoin(body, value);
	if (type == 'T') {
		return (value);
	}
	else {
		return ("                ");
	}
}