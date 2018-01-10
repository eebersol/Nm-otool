

#include "../includes/nm-otool.h"

int main(int ac, char **av)
{
	t_base	*base;
	struct 	stat fileStat;
	char 	*ptr;
	int 	fd;


	if (ac < 2) {
		printf("Nm need argument\n");
		return 1;
	}
	else
	{
		base 		= recover_base();
		fd 			= 0;
		base->name 	= av[1];
		if ((fd = open(base->name, O_RDONLY)) < 0){
			printf("[ERROR] - > open\n");
			return 1;
		}
		if (fstat(fd, &fileStat) < 0)
		{
			printf("[ERROR] - > fStats\n");
			return 1;
		}
		if ((ptr = mmap(0, fileStat.st_size, PROT_READ|PROT_EXEC ,MAP_SHARED , fd, 0)) == MAP_FAILED) {
			printf("[ERROR] - > mmap\n");
			return 1;			
		}
		nm(ptr);
		if ((munmap(ptr, fileStat.st_size)) < 0) {
			printf("[ERROR] - > munmap\n");
			return 1;					
		}
		return 0;

	}

}