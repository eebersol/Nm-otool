#include "../includes/nm-otool.h"

void print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	struct nlist_64 *array;
	int 			i;
	char 			*stringable;

	array 		= ptr + symoff;
	stringable 	= ptr + stroff;
	i 			= 0;
	while(i < nsyms)
	{
		// printf("\n\nn_strx - > %s\n", stringable + array[i].n_un.n_strx);
		// printf("n_type - > %hhu\n", array[i].n_type);
		// printf("n_sect - > %hhu\n", array[i].n_sect);
		// printf("n_desc - > %hu\n", array[i].n_desc);


		printf("%s: ", recover_base()->name);
		if (atoi(ft_itoa(array[i].n_type)) == 15) {
			printf("%.16llx", array[i].n_value);
			printf(" T ");
		}
		else if (array[i].n_type == N_STAB)
			printf("N_STAB ");
		else if (array[i].n_type == N_PEXT)
			printf("N_PEXT ");
		else if (array[i].n_type == N_TYPE) {
			printf("%.16llx", array[i].n_value);
			printf(" b ");
		}
		else if (array[i].n_type == N_EXT) {
			printf("                 U ");
		}
		else
			printf("%s ", ft_itoa(array[i].n_type));

		printf("%s\n", stringable + array[i].n_un.n_strx);
		i++;
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

}