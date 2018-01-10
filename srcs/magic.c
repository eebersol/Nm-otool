#include "../includes/nm-otool.h"

void print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	t_base 			*base;
	t_magic 		*magic;
	struct nlist_64 *array;
	char 			*stringable;
	int 			i;

	base 				= recover_base();
	base->magicBase 	= (t_magic*)malloc(sizeof(t_magic));
	magic 				= base->magicBase;
	array 				= ptr + symoff;
	stringable 			= ptr + stroff;
	i 					= 0;
	while(i < nsyms)
	{
		// printf("\n\nn_strx - > %s\n", stringable + array[i].n_un.n_strx);
		// printf("n_type - > %hhu\n", array[i].n_type);
		// if (ft_strcmp(stringable + array[i].n_un.n_strx, "_shortcuts") == 0) {
		// 	printf("n_sect - > %s :  %u\n",stringable + array[i].n_un.n_strx, array[i].n_sect);
		// 	printf("n_desc - > %u\n", swap_uint16(array[i].n_desc));
		// }
		magic->content 		= &array[i];
		magic->name_func 	= stringable + array[i].n_un.n_strx;
		magic->type 		= get_type(array[i].n_type, magic);
		magic->value 		= get_value(array[i].n_value, magic);
		i++;
		if (i < nsyms)
		{
			magic->next 		= (t_magic*)malloc(sizeof(t_magic));
			magic 				= magic->next;
		}
	}
}

void	add_seg (struct load_command *lc)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i 	= 0;
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	while (i < seg->nsects)
	{
		//printf("sec->name :: %s\n", sec->sectname);
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void handle_64 (char *ptr)
{
	struct 	mach_header_64 		*header;
	struct 	load_command 		*lc;
	struct 	symtab_command		*sym;
	struct 	segment_command_64 *sc;
	int 						ncmds;
	int 						i;

	header 			= (struct mach_header_64 *)ptr;
	lc 				= (void *)ptr + sizeof(*header);
	sc 				= (void *)ptr + sizeof(*header);
	ncmds 			= header->ncmds;
	i 				= 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			// printf("LC_SEGMENT_64\n");
			// printf("\nsc->name : |%s| - ", sc->segname);
			// printf("sc->flags : |%u|\n", swap_uint32(sc->flags));
			add_seg(lc);
		}
		// else if (lc->cmd == LC_ROUTINES_64)
		// {
		// 	printf("LC_ROUTINES_64\n");
		// }
		else if (lc->cmd == LC_SYMTAB)
		{
			// printf("LC_SYMTAB\n");
			sym 	= (struct 	symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		sc = (void*)sc + lc->cmdsize;
	}
	print_nm();

}