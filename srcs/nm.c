#include "../includes/nm-otool.h"

void nm (char *ptr) 
{
	unsigned int  magic_number;

	magic_number  = *(int *)ptr;

	printf("MAGIC NUMBER [%u] [%u] [%u] [%u] [%u]\n", magic_number, MH_MAGIC_64, MH_CIGAM_64, LC_SEGMENT_64, LC_ROUTINES_64);
	if (magic_number == MH_MAGIC_64) {
		printf("It's MH_MAGIC_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_CIGAM_64) {
		printf("It's MAGIC_CIGAM_64\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC) {
		printf("It's MAGIC_MAGIC_32\n");
	}
	else if (magic_number == MH_CIGAM) {
		printf("It's MAGIC_CIGAM_32\n");
	}
	else if (magic_number == FAT_MAGIC) {
		handle_fat(ptr);
		printf("It's FAT_MAGIC\n");
	}
	else if (magic_number == FAT_CIGAM) {
		handle_fat(ptr);
		printf("It's FAT_CIGAM\n");
	}
	else
		printf("It's UNKNOW\n");
}