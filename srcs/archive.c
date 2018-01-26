/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 15:28:54 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void			add_archive(void)
{
	t_base		*base;
	t_archive	*archive;
	t_magic		*magic;

	base = recover_base();
	archive = base->archiveBase;
	magic = base->magicBase;
	while (archive)
	{
		if (ft_strcmp(archive->name, base->path_name) == 0)
			archive->magicArchive = magic;
		if (archive->next == NULL)
			break ;
		archive = archive->next;
	}
}

t_archive		*get_archive(uint32_t off, char *ptr, t_archive *archive)
{
	struct ar_hdr	*arch;

	arch = (void*)ptr + off;
	archive->path_name = arch->ar_name;
	archive->name = get_name(arch->ar_name);
	archive->size_name = get_size(arch->ar_name);
	archive->addr = (void*)arch + sizeof(*arch) + archive->size_name;
	return (archive);
}

void			browse_archive(void)
{
	t_base		*base;
	t_archive	*archive;

	base = recover_base();
	archive = base->archiveBase;
	while (archive)
	{
		if (!archive->name)
			break ;
		base->path_name = archive->name;
		while (archive->next
			&& ft_strcmp(base->path_name, archive->next->name) == 0
				&& base->nm == true)
			archive = archive->next;
		identify_file(archive->addr);
		if (archive->next == NULL)
			break ;
		archive = archive->next;
	}
}

void			handle_archive(char *ptr)
{
	t_archive		*archive;
	struct ar_hdr	*arch;
	struct ranlib	*ran;
	char			*test;
	int				i;
	int				size;

	i = 0;
	arch = (void*)ptr + SARMAG;
	size = get_size(arch->ar_name);
	test = (void*)ptr + sizeof(*arch) + SARMAG + size;
	ran = (void*)ptr + sizeof(*arch) + SARMAG + size + 4;
	size = *((int *)test) / sizeof(struct ranlib);
	recover_base()->archiveBase = (t_archive*)malloc(sizeof(t_archive));
	archive = recover_base()->archiveBase;
	if (size == 0)
	{
		archive->name = "unknow";
		archive->magicArchive = NULL;
		archive->next = NULL;
		return ;
	}
	while (i < size)
	{
		archive = get_archive(ran[i].ran_off, ptr, archive);
		i++;
		if (i < size)
			archive->next = (t_archive*)malloc(sizeof(t_archive));
		archive = archive->next;
	}
	browse_archive();
}
