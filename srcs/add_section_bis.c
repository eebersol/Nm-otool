#include "../includes/nm-otool.h"

static void			add_seg(struct load_command *lc, t_sectionType *sectionType)
{
	unsigned int				i;
	int 						j;
	t_base 						*base;
	struct section_64			*sec;
	struct segment_command_64	*seg;

	i = 0;
	j = 1;
	base = recover_base();
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)(seg + sizeof(seg) / sizeof(void*));
//	printf("1 :: sectionType->name : %s\n", sectionType->name);
	if (base->sectionBase != NULL)
	{
		while (sectionType && sectionType->next)
		{
			if (sectionType->next == NULL)
				break;
			sectionType = sectionType->next;
		}
	}
//	printf("2 :: sectionType->name : %s\n", sectionType->name);
	if (sectionType && sectionType->next == NULL)
	{
		sectionType->next = (t_sectionType*)malloc(sizeof(t_sectionType));
		j = sectionType->nb + 1;
		sectionType = sectionType->next;
	}
	while (i < seg->nsects)
	{
//		printf("add_seg :%s\n", sec->sectname);
		sectionType->name 		= ft_strdup(sec->sectname);
		sectionType->nb 		= j;
		j++;
		i++;
		if (i == seg->nsects)
			sectionType->next 	= NULL;
		else
		{
			sectionType->next 	= (t_sectionType*)malloc(sizeof(t_sectionType));
			sectionType 		= sectionType->next;
		}
		sec = (struct section_64 *)(((void*)sec) + sizeof(struct section_64));
	}
//	printf("add_seg : final len : %d\n\n", lst_count_section(base->sectionBase));
}

void		get_section(struct load_command *lc, struct mach_header_64 *header)
{
	t_sectionType		*sectionType;
	t_base 				*base;
	unsigned int		i;

	i = 0;
	base = recover_base();

	if ((base->sectionBase = (t_sectionType*)malloc(sizeof(t_sectionType))) == NULL)
		return ;
	sectionType = base->sectionBase;
	while (i < header->ncmds)
	{
//		printf("get section i : %d/%d\n",i, header->ncmds);
		if (lc->cmd == LC_SEGMENT_64)
		{
//			printf("get section : find LC_SEGMENT_64\n");
			add_seg(lc, sectionType);
		}
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
	ft_putstr("ICI");
	ft_putnbr(lst_count_section(base->sectionBase));

	i = 0;
	while (base->sectionBase)
	{
		ft_putnbr(i);
		ft_putstr(base->sectionBase->name);
		ft_putnbr(base->sectionBase->nb);
		if (base->sectionBase->next == NULL)
			break;
		i++;
		base->sectionBase = base->sectionBase->next;
	}
//	printf("get_section END : %d\n", lst_count_section(base->sectionBase));
}
