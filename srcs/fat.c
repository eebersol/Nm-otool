#include "../includes/nm-otool.h"

void handle_fat (char *ptr)
{
	struct 	fat_header 		*fat;
	struct 	fat_arch		*arch;
	uint32_t				i;
	uint32_t				offset;

	fat 		= (void*)ptr;
	i 			= swap_uint32(fat->nfat_arch);
	arch 		= ((void*)ptr) + sizeof(fat);
	while (i)
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
		{
			offset = arch->offset;
		}
		else if (swap_uint32(arch->cputype) == CPU_TYPE_I386) {
			ft_putstr("Wrong architecture : CPU_TYPE_I386 are not supported.\n");
			return ;
		}
		else if (swap_uint32(arch->cputype) == CPU_TYPE_POWERPC)
		{
			ft_putstr("Wrong architecture : CPU_TYPE_POWERPC are not supported.\n");
			return ;
		}
		arch += sizeof(struct fat_arch);
		i--;
	}
	identify_file(ptr + swap_uint32(offset));
}