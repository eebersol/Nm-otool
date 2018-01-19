#include "../includes/nm-otool.h"

void print_output_nm(int nsyms, int symoff, int stroff, void *ptr, struct 	load_command *lc)
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
		magic->content 		= &array[i];
		magic->name_func 	= stringable + array[i].n_un.n_strx;
		// if (swap_uint32(array[i].n_desc) != 0)
		magic->addr 		= ptr;
		magic->lcStruct 	= lc;
		magic->type 		= get_type(array[i].n_type, magic);
		magic->value 		= get_value(array[i].n_value, magic);
		// if (magic->type != 'X')
		// 	printf("\n\nName : %su\nValue : %s\nType : %c\n", magic->name_func, magic->value, magic->type);
		i++;
		if (i < nsyms)
		{
			magic->next 		= (t_magic*)malloc(sizeof(t_magic));
			magic 				= magic->next;
		}
	}
}

void	display_check()
{
	t_base *base;

	base = recover_base();
	while (base->magicBase)
	{
		printf("%c  -- %s -- %s", base->magicBase->type, base->magicBase->value, base->magicBase->text_section);
		if (base->magicBase->next == NULL)
			break;
		base->magicBase = base->magicBase->next;
	}
}



void print_output_otool(int nsyms, int symoff, int stroff, void *ptr)
{
	t_base 			*base;
	t_magic 		*magic;
	struct nlist_64 *array;
	char 			*stringable;
	int 			i;

	base 				= recover_base();
	if (base->magicBase  == NULL)
		base->magicBase 	= (t_magic*)malloc(sizeof(t_magic));
	else
		base->magicBase = lst_reverse(base->magicBase);
	magic 				= base->magicBase;
	array 				= ptr + symoff;
	stringable 			= ptr + stroff;
	i 					= 0;
	while(i < nsyms)
	{
		magic->content 		= &array[i];
		magic->name_func 	= stringable + array[i].n_un.n_strx;
		magic->type 		= get_type(array[i].n_type, magic);
		magic->value 		= get_value(array[i].n_value, magic);
		i++;
		if (i < nsyms && magic->type != 'b' && magic->next == NULL)
		{
			magic->next 		= (t_magic*)malloc(sizeof(t_magic));
			magic 				= magic->next;
		}
		else if ((i < nsyms && magic->type != 'b' && magic->next))
		{
			magic 				= magic->next;
		}
	}
	base->magicBase = lst_reverse(base->magicBase);
	//printf("Check in print_output_otool\n");
	//display_check();
}


void	check_seg (struct load_command *lc, struct mach_header_64 *header)
{
	unsigned int				i;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)\
					(seg + sizeof(struct segment_command_64*) / sizeof(void*));
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
			// if (!ft_strcmp(sec->sectname, SECT_DATA))
			// {
			// 	printf("1\n");
			// 	return;
			// }
			// else if (!ft_strcmp(sec->sectname, SECT_BSS))
			// {
			// 	printf("2\n");
			// 	return;
			// }
			// else if (!ft_strcmp(sec->sectname, SECT_TEXT))
			// {
			// 	printf("3\n");
			// 	return;
			// }
			// else
			// 	return;
			get_content(sec->addr, sec->size, (char *)header + sec->offset);
		}
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		i++;
	}
}

void			get_content(uint64_t addr, unsigned int size, char *ptr)
{
	t_base 			*base;
	t_magic 		*magic;
	unsigned int	i;
	char			*str;
	char 			*test_addr;

	base 				= recover_base();
	base->magicBase 	= (t_magic*)malloc(sizeof(t_magic));
	i 					= 0;
	magic 				= base->magicBase;
	magic->text_section = NULL;
	str 				= "";
	while (i < size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			test_addr = get_value_otool_manager(swap_uint64(addr));
		}
		str = ft_strjoin(str, itoa_base(ptr[i], 16, 2));
		str = ft_strjoin(str, " ");
		if ((i + 1) % 16 == 0)
		{
			if(i + 1 != size)
			{
				magic->next 		= (t_magic*)malloc(sizeof(t_magic));
				magic->text_section = (char*)malloc(sizeof(char*) * ft_strlen(str) + 1);
				magic->text_section = str;
				magic->value 		= test_addr;
				magic 				= magic->next;
			}
			if (i + 1 == size)
				break;
			str 				= "";
		}
		i++;
	}
	if (str && ft_strlen(str) > 1 && magic->text_section == NULL){
		magic->text_section = (char*)malloc(sizeof(char*) * ft_strlen(str) + 1);
		magic->text_section = str;	
		magic->value 		= test_addr;
		magic->next 		= NULL;
	}
}

void handle_64 (char *ptr)
{
	t_base *base;
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
	base = recover_base();
	get_section(lc, header);
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64 && recover_base()->nm == false)
		{
			check_seg(lc, header);
		}
		else if (lc->cmd == LC_ROUTINES_64)
		{
			printf("LC_ROUTINES_64\n");
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			sym 	= (struct 	symtab_command *)lc;
			if (recover_base()->nm == true)
			{
				print_output_nm(sym->nsyms, sym->symoff, sym->stroff, (void *)ptr, lc);
			}
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		sc = (void*)sc + lc->cmdsize;
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