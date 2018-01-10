#include "../includes/nm-otool.h"

// void resolve_fat (int ncmds, struct fat_arch *fat_arch, int i)
// {
// 	uint32_t		offset;
// 	uint32_t		size;
// 	uint32_t		align;
// 	void 			*str;
// 	cpu_type_t		cputype;
// 	cpu_subtype_t	cpusubtype;

// 	(void)ncmds;

// 	offset 		= swap_uint32(fat_arch->offset);
// 	size 		= swap_uint32(fat_arch->size);
// 	align 		= swap_uint32(fat_arch->align);
// 	cputype 	= fat_arch->cputype;
// 	cpusubtype 	= fat_arch->cpusubtype;
// 	str 		= fat_arch + offset;

// 	if (offset != 0 || size != 0 || align != 0 || cpusubtype != 0 || cputype != 0) {
// 		printf("\n\n [ %d ]\n\n", i);
// 		printf("Name : %s\n", 	(char*)fat_arch);
// 	//	printf("Name : %s\n", 	(char*)str);
// 	//	printf("ARCH : |%s|%zu\n", 	(char*)str, ft_strlen((char*)str));
// 	//	printf("STR : |%s|\n", 		(char*)str);
// 		printf("offset : %u\n", 	offset);
// 		printf("size : %u\n", 		size);
// 		printf("align : %u\n", 		align);
// 		printf("cputype : %d\n", 	cputype);
// 		printf("cpusubtype : %d\n", cpusubtype);
// 	}
// }

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