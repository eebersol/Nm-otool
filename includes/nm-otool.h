/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:44:53 by eebersol          #+#    #+#             */
/*   Updated: 2018/01/23 16:05:38 by eebersol         ###   ########.fr       */
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

# define FLAG_PROT			PROT_WRITE | PROT_READ
# define FLAG_MAP			MAP_ANON | MAP_PRIVATE
# define INT_MAX			2147483688
# define Err_mummap			": No such file or directory.\n"
# define Err_fstats			": fstats failed.\n"
# define Err_mmap			": mmap failed.\n"
# define Err_open			": No such fil or directory.\n"

typedef	struct				s_section
{
	struct s_segment		*seg;
	struct s_section		*next;
}							t_section;


typedef	struct				s_segment
{
	char					*name;
	int						nb;
	struct s_segment		*next;
}							t_segment;


typedef	struct				s_sectionType
{
	char					*name;
	int						nb;
	struct s_sectionType	*next;
}							t_sectionType;


typedef	struct				s_magic
{
	char					*name_func;
	char					type;
	char					*value;
	char					*text_section;
	void					*addr;
	struct s_magic			*next;
	struct nlist_64			*content;
	struct nlist			*content_32;
}							t_magic;

typedef	struct				s_archive
{
	char					*name;
	char					*path_name;
	int						size_name;
	void					*addr;
	bool					display;
	t_magic					*magicArchive;
	struct s_archive		*next;
}							t_archive;

typedef	struct				s_base
{
	bool					nm;
	bool					archive;
	bool					archiveNm;
	bool					print_name;
	bool					opt_o;
	int						type_arch;
	char					*name;
	char					*path_name;
	char					*nameArchive;
	int						err;
	int						index;
	t_magic					*magicBase;
	t_archive				*archiveBase;
	t_section				*sectionBase;
}							t_base;

void	lstdel_at(t_archive **archive, int at);
void	remove_doublon(void);
void debug(void);
void						add_seg(struct load_command *lc, t_section *section);
unsigned int				get_end(struct load_command *lctmp, unsigned int len);
void						get_section(struct load_command *lc,
											struct mach_header_64 *header, unsigned int len);
void						add_seg_32(struct load_command *lc, t_section *section);
unsigned int				get_end_32(struct load_command *lctmp,  unsigned int len);
void						get_section_32(struct load_command *lc,
											struct mach_header *header, unsigned int len);
void						add_archive(void);
t_archive					*get_archive(uint32_t off, char *ptr, t_archive *archive);
void						browse_archive();
void						handle_archive(char *ptr);
void						handle_fat (char *ptr);
char						get_char_32(t_segment *segment, t_magic *magic);
char						get_char(t_segment *segment, t_magic *magic);
char						browse_section_32(t_magic *magic);
char						browse_section(t_magic *magic);
char						get_type(uint8_t n_type, t_magic *magic);
char						*get_value(uint64_t n_value);
char						*get_name(char *name);
int							get_size(char *name);
char						*get_value_otool_archive(uint64_t n_value);
char						*get_value_otool_exec(uint64_t n_value);
char						*val_otool(uint64_t n_value);
t_base						*recover_base(void);
t_base						*init_base(char *name);
void						get_data_nm(int nsyms, int symoff, int stroff, void *ptr);
void						check_seg(struct load_command *lc, struct mach_header_64 *header);
void						get_content(uint64_t addr, unsigned int size, char *ptr);
void						handle_64(char *ptr);
void						check_seg_32 (struct load_command *lc, struct mach_header *header);
void						get_data_nm_32(int nsyms, int symoff, int stroff, void *ptr);
void						handle_32 (char *ptr);
void						parse_file(t_base *base, int ac, char **av, int i);
void						identify_file (char *ptr);
void						print_err(char  *err);
void						print_manager(void);
void						print_nm(void);
void						print_otool(void);
void						print_archive(void);
void						print_label(void);
void						print_label_archive(t_archive *archive);
void						print_value_archive(t_archive *archive);
void						print_value_nm(t_magic *magic);
uint16_t					swap_uint16(uint16_t nb);
uint32_t					swap_uint32(uint32_t nb);
uint64_t					swap_uint64(uint64_t nb);
char						*str_lower(char *str);
char						read_tab(int i);
char						*itoa_base(int val, int base, int output_size);
t_magic						*add_list(t_magic *magic, char *str, char *test_addr, int flag);
int							cmp_name(char *str1, char *str2);
void						resort_diff(void);
void						sort_alphanumeric(t_magic *node);
void						swap_archive(t_archive *node1, t_archive *node2);
void						sort_alphanumeric_archive(t_archive *node);
int							lst_count(t_magic *lst);
int							lst_count_archive(t_archive *lst);
int							lst_count_section(t_section *lst);
t_magic						*lst_reverse(t_magic *root);

#endif
