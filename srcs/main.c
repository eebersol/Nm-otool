

#include "../includes/nm-otool.h"

int main(int ac, char **av)
{
	t_base	*base;
	struct 	stat fileStat;
	char 	*ptr;
	int 	fd;
	int 	i;
	int 	err;

	if (ac < 2) 
	{
		printf("Nm need argument\n");
		return 1;
	}
	else
	{
		base 				= recover_base();
		err 				= 0;
		i 					= 0;
		if (strcmp(av[0], "./ft_nm") == 0)
			base->nm = true;
		else
			base->nm = false;
		while (++i < ac)
		{
			base->magicBase = NULL;
			base->name 		= av[i];
			base->err 		= false;
			fd 				= 0;
			if ((fd = open(base->name, O_RDONLY)) < 0){
				print_err_open();
			}
			else if (fstat(fd, &fileStat) < 0)
			{
				print_err_fstats();
			}
			else if ((ptr = mmap(0, fileStat.st_size, PROT_READ|PROT_EXEC ,MAP_SHARED , fd, 0)) == MAP_FAILED) {
				print_err_mmap();			
			}
			if (base->err == 0) {
				identify_file(ptr);
				if (base->archive == true)
					print_archive();
			}
			if (base->err == 0 && (munmap(ptr, fileStat.st_size)) < 0) {
				print_err_munmap();		
			}
			if (base->err)
				err++;
		}
		if (err) {
			//ft_putstr("Some error ocured Nm\n");
			return 1;
		}
		return 0;
	}

}