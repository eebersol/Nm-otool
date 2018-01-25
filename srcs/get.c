/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/25 14:07:56 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

char		get_char_32(t_segment *segment, t_magic *magic)
{
	t_segment	*tmp_segment;

	tmp_segment = segment;
//	printf("HI %d\n", lst_count_segment(tmp_segment));
	while (tmp_segment)
	{
		//printf("count\n");
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content_32->n_sect)
		{
			//printf("tmp_segment->name %s\n", tmp_segment->name);
			if (!ft_strcmp(tmp_segment->name, SECT_DATA))
			{
				//printf("D\n");
				return ('D');
			}
			else if (ft_strcmp(tmp_segment->name, "__common") == 0)
				return ('B');
			else if (!ft_strcmp(tmp_segment->name, SECT_BSS) || ft_strcmp(tmp_segment->name, "__common") == 0)
			{
			//	printf("B\n");
				return ('S');
			}
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
			{
				//printf("T\n");
				return ('T');
			}
			else if (ft_strcmp(tmp_segment->name, "__dyld") == 0)
			{
				return ('D');
			}
			else
			{
			//	printf("S\n");
				return ('S');
			}
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
	//printf("Len segment : %d\n", lst_count_segment(tmp_segment));
	while (tmp_segment)
	{
		if (tmp_segment->name != NULL
			&& tmp_segment->nb == magic->content->n_sect)
		{
		//	printf("%s - %d - %u\n", tmp_segment->name, tmp_segment->nb, magic->content->n_sect);
			if (!ft_strcmp(tmp_segment->name, SECT_DATA))
			{
			//	printf("D\n");
				return ('D');
			}
			else if (!ft_strcmp(tmp_segment->name, SECT_BSS))
			{
				//printf("B\n");
				return ('B');
			}
			else if (!ft_strcmp(tmp_segment->name, SECT_TEXT))
			{
				//printf("T\n");
				return ('T');
			}
			else
			{
				//printf("S\n");
				return ('S');
			}
		}
		if (tmp_segment->next == NULL)
			break ;
		tmp_segment = tmp_segment->next;
	}
	return ('X');
}

char		get_type(uint8_t n_type, t_magic *magic)
{
	char c;

	(void)magic;
	(void)n_type;
	//printf("\t-Begin\n");
	if ((n_type & N_TYPE) == N_LSYM || (n_type & N_TYPE) == N_BINCL)
		c = 'X';
	else if ((n_type & N_TYPE) == N_UNDF)
		c = 'U';
	else if ((n_type & N_TYPE) == N_ABS)
		c = 'A';
	else if ((n_type & N_TYPE) == N_SECT && recover_base()->type_arch != 2)
	{
		//if (ft_strcmp(magic->name_func, "_debugTimer") == 0)
		//	printf("Name func : %s\n", magic->name_func);
		c = browse_section(magic);
	}
	else if ((n_type & N_TYPE) == N_SECT && recover_base()->type_arch == 2)
	{
		//if (ft_strcmp(magic->name_func, "_gCRAnnotations") == 0)
		//	printf("Name func : %s\n", magic->name_func);
		c = browse_section_32(magic);
	}
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