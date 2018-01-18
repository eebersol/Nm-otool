#include "../includes/nm-otool.h"

// static void			add_seg(struct load_command *lc, t_sectionType *sectionType)
// {
// 	unsigned int				i;
// 	t_base 						*base;
// 	struct section_64			*sec;
// 	struct segment_command_64	*seg;
// 	t_sectionType *test;
	
// 	i = 0;
// 	base = recover_base();
// 	seg = (struct segment_command_64*)lc;
// 	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
// 	test = sectionType;
// 	//ft_putstr("Begin add_seg: \n\n");
// 	if (sectionType && lst_count_section(sectionType) > 1)
// 	{
// 	//	ft_putstr("second passage \n\n");
// 	//	ft_putnbr(lst_count_section(sectionType));
// 		while (sectionType)
// 		{
// 			if (sectionType->next == NULL)
// 			{
// 				sectionType->next 			= (t_sectionType*)malloc(sizeof(t_sectionType));
// 				sectionType->next->name 	= ft_strdup(sec->sectname);
// 				sectionType->next->nb		= sectionType->nb;
// 				break;
// 			}
// 			sectionType = sectionType->next;
// 		}
// 	}
// 	else 
// 	{
// 	//	ft_putstr("premier passage : \n\n");
// 		sectionType 			= (t_sectionType*)malloc(sizeof(t_sectionType));
// 		sectionType->name 		= ft_strdup(sec->sectname);
// 		sectionType->nb 		= 1;
// 		sectionType				= sectionType->next;
// 	}
// 	while (i < seg->nsects)
// 	{
// 		sectionType 			= (t_sectionType*)malloc(sizeof(t_sectionType));
// 		sectionType->name 		= ft_strdup(sec->sectname);
// 		sectionType->nb 		= sectionType->nb + 1;
// 		sectionType 			= sectionType->next;
// 		i++;
// 		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
// 	}
// 	//ft_putstr("End : \n\n");
// 	printf("Len : %d\n", lst_count_section(test));
// }

// void		get_section(struct load_command *lc, struct mach_header_64 *header)
// {
// 	t_sectionType		*sectionType;
// 	t_sectionType		*tmp;
// 	t_base 				*base;
// 	unsigned int		i;

// 	i = 0;
// 	base = recover_base();

// 	//ft_putstr("TRUE : ");
// 	//ft_putnbr(lst_count_section(base->sectionBase));
// 	//ft_putstr(" \n");
// 	sectionType = NULL;
// 	sectionType = base->sectionBase;
// 	if ((base->sectionBase = (t_sectionType*)malloc(sizeof(t_sectionType))) == NULL)
// 		return ;
// 	//ft_putstr("Begin get_section : ");
// 	//ft_putnbr(lst_count_section(sectionType));
// 	//ft_putstr(" \n");
// 	while (i < header->ncmds)
// 	{
// 		if (lc->cmd == LC_SEGMENT_64)
// 		{
// 			printf("Enter\n");
// 			add_seg(lc, sectionType);
// 		}
// 		lc += lc->cmdsize / sizeof(void *);
// 		i++;
// 	}
// 	tmp = base->sectionBase;
// 	//ft_putstr("Display : \n\n");
// 	// while (tmp)
// 	// {
// 	// 	ft_putstr("Begin : \n\n");
// 	// 	ft_putstr("Name :");
// 	// 	ft_putstr(tmp->name);
// 	// 	ft_putstr("\n");
// 	// 	ft_putstr("Nbr : ");
// 	// 	ft_putnbr(tmp->nb);
// 	// 	ft_putstr("\n\n");
// 	// 	if (tmp->next == NULL)
// 	// 		break;
// 	// 	tmp = tmp->next;
// 	// }
// }

static void 	add_seg(struct load_command *lc, t_section *section)
{
	struct section_64			*sec;
	struct segment_command_64	*seg;
	t_segment 					*segment;
	unsigned int				i;
	
	i 		= 0;
	seg 	= (struct segment_command_64*)lc;
	sec 	= (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
	section->seg = (t_segment*)malloc(sizeof(t_segment));
	segment = section->seg; 
	while (i < seg->nsects)
	{
		segment->name 		= ft_strdup(sec->sectname);
		if (recover_base()->index && i == 0)
		{
		//	printf("EMTER\n");
			segment->nb = recover_base()->index + 1;
		}
		else if  (i == 0)
			segment->nb 		= 1;
	//	printf("SEGMENT NAME : %s -- %d - %d\n", ft_strdup(sec->sectname), segment->nb, seg->nsects);
		i++;
		if (i < seg->nsects)
		{
			segment->next 			= (t_segment*)malloc(sizeof(t_segment));
			segment->next->nb 		= segment->nb + 1;
			segment					= segment->next;
		}
		else
			break;
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
		if (i == seg->nsects)
			break;
	}
	recover_base()->index = segment->nb;
	segment->next = NULL;
}

static 	unsigned int 	get_end(struct load_command *lctmp, unsigned int len)
{
	unsigned int i;
	unsigned int count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (lctmp->cmd == LC_SEGMENT_64)
			count++;
		lctmp += lctmp->cmdsize / sizeof(void *);
		i++;
	}
	return (count);
}
void		get_section(struct load_command *lc, struct mach_header_64 *header)
{
	t_base 				*base;
	t_section			*section;
	t_section			*sectionTMP;
	unsigned int		i;
	unsigned int 		len;
	unsigned int 		k;

	i 					= 0;
	k 					= 0;
	base 				= recover_base(); 
	base->sectionBase 	= (t_section*)malloc(sizeof(t_section));
	section 			= base->sectionBase;
	sectionTMP 			= section;
	len 				= get_end(lc, header->ncmds);
	i = 0;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			k++;
			add_seg(lc, section);
			if (k < len)
			{
				section->next 	= (t_section*)malloc(sizeof(t_section));
				section 		= section->next;
			}
			else
				section->next = NULL;
		}
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
}
