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
	array 		= ptr + symoff;
	stringable 	= ptr + stroff;
	i 			= 0;
	while(i < nsyms)
	{
		// printf("\n\nn_strx - > %s\n", stringable + array[i].n_un.n_strx);
		// printf("n_type - > %hhu\n", array[i].n_type);
		// printf("n_sect - > %hhu\n", array[i].n_sect);
		// printf("n_desc - > %hu\n", array[i].n_desc);
		magic->type 		= get_type(array[i].n_type);
		magic->value 		= get_value(array[i].n_value, magic->type);
		magic->name_func 	= stringable + array[i].n_un.n_strx;
		i++;
		if (i < nsyms)
		{
			magic->next 		= (t_magic*)malloc(sizeof(t_magic));
			magic 				= magic->next;
		}
	}
}

void handle_64 (char *ptr)
{
	struct 	mach_header_64 	*header;
	struct 	load_command 	*lc;
	struct 	symtab_command	*sym;
	int 					ncmds;
	int 					i;

	header 			= (struct mach_header_64 *)ptr;
	ncmds 			= header->ncmds;
	lc 				= (void *)ptr + sizeof(*header);
	i 				= 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym 	= (struct 	symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	print_handle_64();

}