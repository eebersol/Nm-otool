#include "../includes/nm-otool.h"

void	printf_prg_name()
{
	if (recover_base()->name) {
		ft_putstr(recover_base()->name);
	} else
		ft_putstr("print_prg_name -> ERROR");
}

void	print_handle_64()
{
	t_base 	*base;
	t_magic *magic;

	base 	= recover_base();
	magic 	= base->magicBase;
	pairWiseSwap(magic);
	while (magic)
	{
		printf_prg_name();
		ft_putstr(": ");
		ft_putstr(magic->value);
		ft_putchar(' ');
		ft_putchar(magic->type);
		ft_putchar(' ');
		ft_putstr(magic->name_func);
		ft_putchar('\n');
		if (magic->next == NULL)
			break;
		magic = magic->next;
	}
}