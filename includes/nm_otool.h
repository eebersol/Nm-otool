/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/20 11:01:45 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <ar.h>
# include <mach-o/ranlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/dyld.h>
# include <mach-o/stab.h>
# include <mach-o/ranlib.h>
# include <mach/machine.h>
# include "../libft/libft.h"
# define FLAG_PROT		PROT_WRITE | PROT_READ
# define FLAG_MAP		MAP_ANON | MAP_PRIVATE
# define INT_MAX		2147483688
# define ERR_MUMMAP		"nm : No such file or directory.\n"
# define ERR_FSTATS		"nm : fstats failed.\n"
# define ERR_MMAP		"nm : mmap failed.\n"
# define ERR_OPEN		"nm : No such fil or directory.\n"
# define ERR_CORRUPT	"nm : File corrupt"
# define ERR_FORMAT		"nm : Wrong binary format\n"
# define ERR_POWER_PC	"nm : CPU_TYPE_POWERPC are not supported.\n"

typedef	struct			s_segment
{
	char				*name;
}						t_segment;

typedef	struct			s_magic
{
	char				*name_func;
	char				*value;
	char				*text_section;
	char				type;
	uint8_t				n_sect;
}						t_magic;

typedef	struct			s_base
{
	int					ac;
	bool				power_pc;
	unsigned int		file_size;
	bool				nm;
	bool				archive;
	bool				is_alone;
	bool				print_or;
	int					type_file;
	char				*name;
	char				*path_name;
	int					err;
	t_list				*list_magic;
	t_list				*list_segment;
}						t_base;
/*
** NAME : data_magic.c
*/
void					data_magic(int nsyms, int symoff,
									int stroff, void *ptr);
void					data_magic_32(int nsyms, int symoff,
									int stroff, void *ptr);
void					get_content(uint64_t addr, unsigned int size,
									char *ptr);
void					data_seg(struct load_command *lc,
									struct mach_header_64 *header);
void					data_seg_32(struct load_command *lc,
									struct mach_header *header);
/*
** NAME : handle.c
*/
void					handle_archive(char *ptr);
void					handle_fat(char *ptr);
void					handle_64(char *ptr);
void					handle_32(char *ptr);
/*
** NAME : init_struct.c
*/
t_base					*recover_base(void);
t_base					*init_base(char *name);
t_base					*reinit_base(char *name);
/*
** NAME : nm_otool.c
*/
void					parse_file(t_base *base, int ac, char **av, int i);
void					identify_file(char *ptr);
/*
** NAME : print.c
*/
void					print_err(char *err);
void					print_nm(void);
void					print_node(t_base *base, t_magic *magic);
/*
** NAME : section.c
*/
void					segment(struct load_command *lc);
void					segment_32(struct load_command *lc);
/*
** NAME : endian.c
*/
uint32_t				endian_32(uint32_t nb);
uint64_t				endian_64(uint64_t nb);
/*
** NAME : tools.c
*/
char					*itoa_base(int val, int base, int output_size);
void					add_list(char *str, char *test_addr);
void					find_place(t_list *complet_node, t_magic *node);
void					find_best_place(t_base *base, t_list *tmp, int i);
/*
** NAME : type.c
*/
void					check_power_pc(struct fat_header *fat,
												struct fat_arch *arch);
char					get_char(char *name);
char					get_type(uint8_t n_type, t_magic *magic);
/*
** NAME : value.c
*/
char					*padding(int value_len, char *value_l,
											char *value_r, int len);
char					*value(uint64_t n_value, int len);
char					*value_abs(uint64_t n_value, int len);
char					*value_manager(char type, uint64_t n_value);
/*
** NAME : value_otool.c
*/
char					*get_name(char *name);
int						get_size(char *name);
char					*get_value_otool_archive(uint64_t n_value);
char					*get_value_otool_exec(uint64_t n_value);
char					*val_otool(uint64_t n_value);

#endif
