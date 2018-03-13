/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/13 12:40:34 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm_otool.h"

void	identify_file(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		handle_64(ptr);
	else if ((magic_number == MH_MAGIC || magic_number == MH_CIGAM))
	{
		recover_base()->type_file = 2;
		handle_32(ptr);
	}
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
		handle_fat(ptr);
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
	{
		if (recover_base()->nm == false)
			ft_putstr(ft_strjoin("Archive : ", recover_base()->name));
		recover_base()->archive = true;
		handle_archive(ptr);
	}
	else
		print_err(ERR_FORMAT);
}

void	parse_file(t_base *base, int ac, char **av, int i)
{
	struct stat file_stats;
	char		*ptr;
	int			fd;

	while (++i < ac)
	{
		base = init_base(av[i]);
		base->ac = ac;
		fd = 0;
		if ((fd = open(base->name, O_RDONLY)) < 0)
			print_err(ERR_OPEN);
		else if (fstat(fd, &file_stats) < 0)
			print_err(ERR_FSTATS);
		else if ((ptr = mmap(0, file_stats.st_size,
				PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0)) == MAP_FAILED)
			print_err(ERR_MMAP);
		base->file_size = file_stats.st_size;
		if (base->err == 0)
			identify_file(ptr);
		if (base->err == 0 && (munmap(ptr, file_stats.st_size)) < 0)
			print_err(ERR_MUMMAP);
	}
}

int		main(int ac, char **av)
{
	t_base	*base;
	int		i;

	base = recover_base();
	i = 0;
	if (ac >= 2)
	{
		base->nm = ft_strstr(av[0], "ft_nm") != NULL ? true : false;
		parse_file(base, ac, av, i);
	}
	else
	{
		ft_putstr("Program need argument\n");
		base->err++;
	}
	return (base->err > 1 ? 1 : 0);
}
