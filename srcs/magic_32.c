#include "../includes/nm-otool.h"

void	check_seg_32 (struct load_command *lc, struct mach_header *header)
{
	unsigned int				i;
	struct section			*sec;
	struct segment_command	*seg;

	seg = (struct segment_command*)lc;
	sec = (struct section*)\
					(seg + sizeof(struct segment_command*) / sizeof(void*));
	i 	= 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(sec->segname, "__TEXT") == 0 && ft_strcmp(sec->sectname, "__text") == 0)
		{
			if (recover_base()->archive == false && recover_base()->nm == false) {
				ft_putstr(recover_base()->name);
				ft_putstr(":\n");
				ft_putstr("Contents of (__TEXT,__text) section\n");
			}
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section *)(((void*)sec) + sizeof(struct section));
		i++;
	}
}

void get_data_nm_32(int nsyms, int symoff, int stroff, void *ptr, struct load_command *lc)
{
	t_base 			*base;
	t_magic 		*magic;
	struct nlist 	*array;
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
		magic->content_32 		= &array[i];
		magic->name_func 	= stringable + array[i].n_un.n_strx;
		magic->addr 		= ptr;
		magic->lcStruct 	= lc;
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

void handle_32 (char *ptr)
{
	t_base 						*base;
	struct 	mach_header			*header;
	struct 	load_command 		*lc;
	struct 	symtab_command		*sym;
	struct 	segment_command 	*sc;
	int 						ncmds;
	int 						i;  

	base 			= recover_base();
	header 			= (struct mach_header *)ptr;
	lc 				= (void *)ptr + sizeof(*header);
	sc 				= (void *)ptr + sizeof(*header);
	ncmds 			= header->ncmds;
	i 				= 0;
	get_section_32(lc, header);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT && recover_base()->nm == false)
			check_seg_32(lc, header);
		else if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			if (recover_base()->nm == true)
				get_data_nm_32(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr, lc);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		sc = (void *)sc + lc->cmdsize;
	}
	if (recover_base()->nm == true) {
		print_nm();
	}
	else if (recover_base()->archive == true) {
		add_archive();
	}
	else if (recover_base()->nm == false && recover_base()->archive == false) {
		print_otool();
	}
}