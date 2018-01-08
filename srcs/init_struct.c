#include "../includes/nm-otool.h"

t_base	*recover_base(void)
{
	static t_base	base;

	return (&base);
}

void	init_base(void)
{
	t_base	*base;

	base = recover_base();
}
