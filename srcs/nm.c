#include "../includes/nm-otool.h"

void identify_file (char *ptr) 
{
	unsigned int  magic_number;

	magic_number  = *(int *)ptr;
	if (magic_number == MH_MAGIC_64) {
		 //printf("It's MH_MAGIC_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_CIGAM_64) {
		// printf("It's MAGIC_CIGAM_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC) {
		//printf("It's MAGIC_MAGIC_32\n");
		handle_32(ptr);
	}
	else if (magic_number == MH_CIGAM) {
		//ft_putstr("HI 6\n");
		handle_32(ptr);
		//printf("It's MAGIC_CIGAM_32\n");
	}
	else if (magic_number == FAT_MAGIC) {
		// printf("It's FAT_MAGIC\n");
		handle_fat(ptr);
	}
	else if (magic_number == FAT_CIGAM) {
		// printf("It's FAT_CIGAM\n");
		//ft_putstr("HI 5\n");
		handle_fat(ptr);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG)) {
		//ft_putstr("ARCHIVE 1\n");
		if (recover_base()->nm == false)
		{
			recover_base()->archive = true;
		//	ft_putstr("Archive : ");
		//	ft_putstr(recover_base()->name);
		//	ft_putchar('\n');
		}
		else
			recover_base()->archiveNm = true;
		handle_archive(ptr);
	}
	else {
		printf("It's UNKNOW\n");
	}
}