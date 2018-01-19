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