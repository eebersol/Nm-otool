#include "../includes/nm-otool.h"

void	print_err_munmap(void)
{
	recover_base()->err = true;
	ft_putstr("nm: ");
	ft_putstr(recover_base()->name);
	ft_putstr(": No such fil or directory.\n");
}

void	print_err_fstats(void)
{
	recover_base()->err = true;
	ft_putstr("nm: ");
	ft_putstr(recover_base()->name);
	ft_putstr(": fstats failed.\n");
}

void	print_err_mmap(void)
{
	recover_base()->err = true;
	ft_putstr("nm: ");
	ft_putstr(recover_base()->name);
	ft_putstr(": mmap failed.\n");
}

void	print_err_open(void)
{
	recover_base()->err = true;
	ft_putstr("nm: ");
	ft_putstr(recover_base()->name);
	ft_putstr(": No such fil or directory.\n");
}

void	print_nm(void)
{
	t_base 	*base;
	t_magic *magic;

	base 	= recover_base();
	magic 	= base->magicBase;
	sort_alphanumeric(magic);
	while (magic)
	{
		if (magic->type != 'X')
		{
			ft_putstr(base->name);
			ft_putstr(": ");
			if (magic->type == 'S' || magic->type == 'T' || magic->type == 't' || magic->type == 'b' || magic->type == 'd' || magic->type == 'D' || magic->type == 's')
				ft_putstr(magic->value);
			else
				ft_putstr("                ");
			ft_putchar(' ');
			ft_putchar(magic->type);
			ft_putchar(' ');
			ft_putstr(magic->name_func);
			ft_putchar('\n');
		}
		if (magic->next == NULL)
			break;
		magic = magic->next;
	}
}