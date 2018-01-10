#include "../includes/nm-otool.h"

void nm (char *ptr) 
{
	unsigned int  magic_number;

	magic_number  = *(int *)ptr;
	if (magic_number == MH_MAGIC_64) {
		//printf("It's MH_MAGIC_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_CIGAM_64) {
		//printf("It's MAGIC_CIGAM_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC) {
		//printf("It's MAGIC_MAGIC_32\n");
	}
	else if (magic_number == MH_CIGAM) {
		//printf("It's MAGIC_CIGAM_32\n");
	}
	else if (magic_number == FAT_MAGIC) {
		//printf("It's FAT_MAGIC\n");
		handle_fat(ptr);
	}
	else if (magic_number == FAT_CIGAM) {
		//printf("It's FAT_CIGAM\n");
		handle_fat(ptr);
	}
	else if (!ft_strncmp(ptr, ARMAG, SARMAG)) {
		//printf("Archive\n");
		// handle_archive();
	}
	else
		printf("It's UNKNOW\n");
}