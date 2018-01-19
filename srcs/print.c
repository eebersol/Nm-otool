#include "../includes/nm-otool.h"

void	print_nm(void)
{
	t_base 	*base;
	t_magic *magic;

	base 	= recover_base();
	magic 	= base->magicBase;
	//return;
	sort_alphanumeric(magic);
	while (magic)
	{
		//printf("\n\nName : %s\nValue : %s\nType : %c\n", magic->name_func, magic->value, magic->type)
		if (magic->type != 'X' && magic->name_func && ft_strlen(magic->name_func) > 0 
			&& ft_strstr(magic->name_func, "radr:") == NULL && magic->type != 'u')
		{
			if (magic->type == 'S' || magic->type == 'T' || magic->type == 't' || magic->type == 'b' || magic->type == 'd' || magic->type == 'D' || magic->type == 's' || magic->type == 'I')
				ft_putstr(magic->value);
			else
				ft_putstr("                ");
			ft_putchar(' ');
			ft_putchar(magic->type);
			ft_putchar(' ');
			ft_putstr(magic->name_func);
			ft_putchar('\n');
		}
		if (magic->next == NULL)
			break;
		magic = magic->next;
	}
}

void	print_otool(void)
{
	t_base 	*base;
	t_magic *magicTmp;

	base 		= recover_base();
	magicTmp 	= base->magicBase;
	while (magicTmp)
	{
		ft_putstr(magicTmp->value);
		ft_putchar('\t');
		ft_putstr(magicTmp->text_section);
		ft_putchar('\n');
		if (magicTmp->next == NULL) {
			break;
		}
		magicTmp = magicTmp->next;
	}
}

void 	print_archive(void)
{
	t_base 		*base;
	t_archive 	*archive;

	base = recover_base();
	archive = base->archiveBase;
	sort_alphanumeric_archive(archive);
	while (archive)
	{
		ft_putstr(base->name);
		ft_putchar('(');
		ft_putstr(archive->name);
		ft_putstr("):\n");
		ft_putstr("Contents of (__TEXT,__text) section\n");
		if (archive->magicArchive)
		{
			while (archive->magicArchive)
			{
				ft_putstr(archive->magicArchive->value);
				ft_putchar('\t');
				ft_putstr(archive->magicArchive->text_section);
				ft_putchar('\n');
				if (archive->magicArchive->next == NULL)
					break;
				archive->magicArchive = archive->magicArchive->next;	
			}
		}
		if (archive->next == NULL)
			break;
		archive = archive->next;
	}
}

void	 add_archive(void)
{
	t_base 		*base;
	t_archive 	*archive;
	t_magic 	*magic;
	int i;

	base = recover_base();
	archive = base->archiveBase;
	magic 	= base->magicBase;
	i = lst_count_archive(archive);
	while (archive)
	{
		archive->magicArchive = magic;
		// while (magic)
		// {
		// 	printf("In magic list archive\n");
		// 	archive->magicArchive->next = (t_magic*)malloc(sizeof(t_magic));
		// 	archive->magicArchive = magic;
		// 	if (magic->next == NULL)
		// 		break;
		// 	magic = magic->next;
		// 	archive = archive->next;
		// }
		if (archive->next == NULL)
			break;
		archive = archive->next;
	}
}
