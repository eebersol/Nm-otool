/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 16:11:10 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm-otool.h"

void	parse_file(t_base *base, int ac, char **av, int i)
{
	struct stat file_stats;
	char		*ptr;
	int			fd;

	while (++i < ac)
	{
		base = init_base(av[i]);
		fd = 0;
		if ((fd = open(base->name, O_RDONLY)) < 0)
			print_err(Err_open);
		else if (fstat(fd, &file_stats) < 0)
			print_err(Err_fstats);
		else if ((ptr = mmap(0, file_stats.st_size,
				PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED)
			print_err(Err_mmap);
		if (base->err == 0)
		{
			identify_file(ptr);
			print_archive();
		}
		if (base->err == 0 && (munmap(ptr, file_stats.st_size)) < 0)
			print_err(Err_mummap);
	}
}

void	identify_file(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		recover_base()->type_arch = 1;
		handle_64(ptr);
	}
	else if ((magic_number == MH_MAGIC || magic_number == MH_CIGAM) && recover_base()->nm == true)
	{
		recover_base()->type_arch = 2;
		handle_32(ptr);
	}
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		recover_base()->type_arch = 3;
		handle_fat(ptr);
	}	
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
	{
		recover_base()->archive = recover_base()->nm == false ? true : false;
		recover_base()->archiveNm = recover_base()->nm == false ? false : true;
		handle_archive(ptr);
	}
	else 
	{
		recover_base()->err++;
		printf("Wrong binary format\n");
	}
}
