/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/26 17:10:56 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char		get_char_32(t_segment *segment, t_magic *magic)
{
	t_segment	*tmp_segment;

	tmp_segment = segment;
	while (tmp_segment)
	{
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content_32->n_sect)
		{
			// if (ft_strcmp(magic->name_func, "_backtracesContained") == 0)
			// {
			// 	printf("tmp_segment->name %s tmp_segment->nb %d-- %d\n", tmp_segment->name, tmp_segment->nb, ft_strcmp(tmp_segment->name, "__message_refs"));
			// 	if (!ft_strcmp(tmp_segment->name, SECT_OBJC_SYMBOLS))
			// 		printf("1\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_OBJC_MODULES))
			// 		printf("2\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_OBJC_STRINGS))
			// 		printf("3\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_OBJC_REFS))
			// 		printf("4\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_ICON_HEADER))
			// 		printf("5\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_ICON_TIFF))
			// 		printf("6\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_FVMLIB_INIT0))
			// 		printf("7\n");
			// 	if (!ft_strcmp(tmp_segment->name, SECT_FVMLIB_INIT1))
			// 		printf("8\n");
			// 	exit(0);

			// }
			if (ft_strcmp(tmp_segment->name, "__common") == 0 || (ft_strcmp(tmp_segment->name, "__message_refs") == 0  && tmp_segment->nb != 15))
			{
				return ('B');
			}
			else if (!ft_strcmp(tmp_segment->name, SECT_COMMON) 
				|| ft_strcmp(tmp_segment->name, "__dyld") == 0 
					|| ft_strcmp(tmp_segment->name, "__interpose") == 0
						|| (ft_strcmp(tmp_segment->name, "__crash_info") == 0 && tmp_segment->nb != 14))
				return ('D');
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
				return ('T');
			else if (!ft_strcmp(tmp_segment->name, SECT_BSS) || ft_strcmp(tmp_segment->name, "__common") == 0)
				return ('S');
			else
				return ('S');
		}
		if (tmp_segment->next == NULL)
			break ;
		tmp_segment = tmp_segment->next;
	}
	return ('X');
}

char		get_char(t_segment *segment, t_magic *magic)
{
	t_segment	*tmp_segment;

	tmp_segment = segment;
	while (tmp_segment)
	{
			if (ft_strcmp(magic->name_func, "_terminalWidt") == 0)
			{
				printf("tmp_segment->name %s tmp_segment->nb %d\n", tmp_segment->name, tmp_segment->nb);
				if (!ft_strcmp(tmp_segment->name, SECT_OBJC_SYMBOLS))
					printf("1\n");
				if (!ft_strcmp(tmp_segment->name, SECT_OBJC_MODULES))
					printf("2\n");
				if (!ft_strcmp(tmp_segment->name, SECT_OBJC_STRINGS))
					printf("3\n");
				if (!ft_strcmp(tmp_segment->name, SECT_OBJC_REFS))
					printf("4\n");
				if (!ft_strcmp(tmp_segment->name, SECT_ICON_HEADER))
					printf("5\n");
				if (!ft_strcmp(tmp_segment->name, SECT_ICON_TIFF))
					printf("6\n");
				if (!ft_strcmp(tmp_segment->name, SECT_FVMLIB_INIT0))
					printf("7\n");
				if (!ft_strcmp(tmp_segment->name, SECT_FVMLIB_INIT1))
					printf("8\n");
				exit(0);
			
			}
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content->n_sect)
		{
			if (!ft_strcmp(tmp_segment->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp_segment->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		if (tmp_segment->next == NULL)
			break ;
		tmp_segment = tmp_segment->next;
	}
	return ('X');
}

char		browse_section(t_magic *magic, int typeFile)
{
	t_section	*tmp;
	char		c;

	tmp = recover_base()->sectionBase;
	c = 'X';
	while (tmp)
	{
		if (typeFile != 2)
			c = get_char(tmp->seg, magic);
		else
			c = get_char_32(tmp->seg, magic);
		if (c != 'X')
			return (c);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return ('S');
}

char		get_type(uint8_t n_type, t_magic *magic)
{
	char c;

	(void)magic;
	(void)n_type;
	if ((n_type & N_TYPE) == N_LSYM || (n_type & N_TYPE) == N_BINCL)
		c = 'X';
	else if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT)
		c = browse_section(magic, recover_base()->type_arch);
	else if ((n_type & N_TYPE) == N_PBUD)
		c = 's';
	else if ((n_type & N_TYPE) == N_INDR)
		c = 'I';
	else
		c = 'X';
	if ((n_type & N_EXT) == 0 && c != 'X')
		c += 32;
	return (c);
}
