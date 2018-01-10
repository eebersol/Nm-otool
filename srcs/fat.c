#include "../includes/nm-otool.h"

void handle_fat (char *ptr)
{
	struct 	fat_header 		*fat;
	struct 	fat_arch		*arch;
	uint32_t				i;
	uint32_t				offset;

	// printf("Handle fat\n");
	fat 		= (void*)ptr;
	i 			= swap_uint32(fat->nfat_arch);
	arch 		= ((void*)ptr) + sizeof(fat);
	while (i)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(struct fat_arch) /*/ sizeof(void*)*/;
		i--;
	}
	nm(ptr + swap_uint32(offset));
}