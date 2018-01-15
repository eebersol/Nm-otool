#include "../includes/nm-otool.h"

char		*get_name(char *name)
{
	int		length;

	length = ft_strlen(ARFMAG);
	return (ft_strstr(name, ARFMAG) + length);
}

int			get_size(char *name)
{
	int		x;
	char	*word;

	word = ft_strchr(name, '/') + 1;
	x = ft_atoi(word);
	return (x);
}

char 	*str_lower(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (NULL);
	while (i < ft_strlen(str))
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
char 	*get_value_otool_archive(uint64_t n_value)
{
	char 	*value_l;
	char 	*value_r;
	size_t 	value_len;
	int 	padding;


	value_r = str_lower(ft_itoa_base(n_value, 16));
	value_l = ft_itoa_base(swap_uint64(n_value), 16);
	value_len = ft_strlen(value_l) + ft_strlen(value_r);
	if (value_len < 9)
	{
		while (value_len < 9)
		{
			value_l = ft_strjoin("0", value_l);
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
	value_l = ft_strjoin(value_l, value_r);
	value_l = ft_strsub(value_l, 0, ft_strlen(value_l)-1 );
	value_l = ft_strjoin("0", value_l);
	return (value_l);
}

char 	*get_value_otool_exec(uint64_t n_value)
{
	char 	*value_l;
	char 	*value_r;
	char 	*result;
	size_t 	value_len;
	int 	padding;

	padding = 0;
	value_len = 0;
	value_l = ft_itoa_base(n_value, 16);
	value_l = ft_strsub(value_l, 0, ft_strlen(value_l) - 1);
	result = "0000000";
	value_r = str_lower(ft_itoa_base(swap_uint64(n_value), 16));

	if (ft_strlen(result) + ft_strlen(value_l) + ft_strlen(value_r) < 16)
	{
		value_len = ft_strlen(result) + ft_strlen(value_l) + ft_strlen(value_r);
		while (value_len < 16)
		{
			value_l = ft_strjoin(value_l, "0");
			value_len++;
		}
	}
	else if (ft_strlen(result) + ft_strlen(value_l) + ft_strlen(value_r) > 16)
	{
		padding = 16 - (ft_strlen(value_r) + ft_strlen(result));
		value_l = ft_strsub(value_l, 0, padding);
	}
	result = ft_strjoin(result, ft_strjoin(value_l, value_r));
	return (result);
}


char *get_value_otool_manager(uint64_t n_value)
{
	t_base 	*base;
	char 	*ret;

	base = recover_base();
	ret 	= NULL;
	if (base->archive == true)
	{
		ret = get_value_otool_archive(n_value);
	}
	else
	{
		ret = get_value_otool_exec(n_value);
	}
	return (ret);
}