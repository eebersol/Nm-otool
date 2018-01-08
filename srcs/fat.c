#include "../includes/nm-otool.h"

void resolve_fat (int ncmds, void *fat_arch)
{
	(void)ncmds;
	printf("HI\n");
	// printf("%u\n", ((struct fat_arch *)fat_arch)->cputype);
	// printf("%u\n", ((struct fat_arch *)fat_arch)-> cpusubtype);
	printf("%u\n", 	swap_uint32(((struct fat_arch *)fat_arch)->offset));
	printf("HI\n");
	printf("%u\n", 	swap_uint32(((struct fat_arch *)fat_arch)->size));
	printf("HI\n");
	printf("%u\n", 	swap_uint32(((struct fat_arch *)fat_arch)->align));
	printf("HI\n");
}

void handle_fat (char *ptr)
{
	struct 	fat_header 	*header;
	int 				ncmds;
	int 				i;

	header 		= (struct fat_header *)ptr;
	ncmds 		= header->nfat_arch;
	i 			= 0;
	while (i++ < ncmds)
	{
		void *fat_arch = ((void*)header + sizeof(struct fat_header))
					+ (ncmds * sizeof(struct fat_arch));
		resolve_fat(ncmds, fat_arch);

	}  

}
