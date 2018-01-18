#include "../includes/nm-otool.h"

static t_archive	*print_art(uint32_t off, char *ptr, t_archive *archive)
{
	struct ar_hdr	*arch;

	arch 					= (void*)ptr + off;
	archive->path_name 		= arch->ar_name;
	archive->name 			= get_name(arch->ar_name);
	archive->size_fuck 		= get_size(arch->ar_name);
	archive->addr 			= (void*)arch + sizeof(*arch) + archive->size_fuck;
	return (archive);
}

void	handle_archive(char *ptr)
{
	t_base 			*base;
	t_archive 		*archive;
	t_archive 		*tmp_archive;
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	char			*test;
	int				i;
	int				size;
	int				size_fuck;

	i 					= 0;
	arch 				= (void*)ptr + SARMAG;
	size_fuck 			= get_size(arch->ar_name);
	test 				= (void*)ptr + sizeof(*arch) + SARMAG + size_fuck;
	ran 				= (void*)ptr + sizeof(*arch) + SARMAG + size_fuck + 4;
	size 				= *((int *)test);
	size 				= size / sizeof(struct ranlib);
	base 				= recover_base();
	base->archiveBase 	= (t_archive*)malloc(sizeof(t_archive));
	archive 			= base->archiveBase;
	tmp_archive 		= base->archiveBase;
	while (i < size)	
	{	
		printf("JE SUIS ICI\n");
		archive = print_art(ran[i].ran_off, ptr, archive);
		i++;
		if (i < size)
			archive->next = (t_archive*)malloc(sizeof(t_archive));
		archive = archive->next;
	}
	while (tmp_archive)
	{
		base->path_name = tmp_archive->name; 
		while (tmp_archive->next && ft_strcmp(base->path_name, tmp_archive->next->name) == 0 && base->nm == true)
		{
			tmp_archive = tmp_archive->next;
		}
		identify_file(tmp_archive->addr);
		if (tmp_archive->next == NULL)
			break;
		tmp_archive = tmp_archive->next;
	}
}