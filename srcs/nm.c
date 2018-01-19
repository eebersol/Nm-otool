#include "../includes/nm-otool.h"

void identify_file (char *ptr) 
{
	t_base 			*base;
	unsigned int  	magic_number;

	magic_number  	= *(int *)ptr;
	base 			= recover_base();
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64) {
		base->type_arch = 1;
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM) {
		base->type_arch = 2;
		handle_32(ptr);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM) {
		base->type_arch = 3;
		handle_fat(ptr);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG)) {
		if (recover_base()->nm == false)
		{
			recover_base()->archive = true;
		}
		else
			recover_base()->archiveNm = true;
		handle_archive(ptr);
	}
	else {
		printf("It's UNKNOW\n");
	}
}