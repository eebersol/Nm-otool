

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
// typedef	enum				e_zone_type
// {
// 	TINY,
// 	SMALL,
// 	LARGE
// }							t_zone_type;

typedef	struct				s_magic
{
	char					*name_func;
	char					type;
	char 					*value;
	char 					*text_section;
	struct s_magic			*next;
	struct nlist_64			*content;
}							t_magic;

typedef	struct				s_archive
{
	char 					*name;
	int 					size_fuck;
	void 					*addr;
	t_magic 				*magicArchive;
	struct s_archive		*next;
}							t_archive;

typedef	struct				s_base
{
	bool					nm;
	bool					archive;
	char 					*name;
	char 					*nameArchive;
	bool					err;
	t_magic 				*magicBase;
	t_archive				*archiveBase;
}							t_base;

// delcare function 

// init_struct.c //
void						init_base(void);
t_base						*recover_base(void);

// nm.c //
void 						identify_file (char *ptr);

// fat.c //
void 						handle_fat (char *ptr);

// magic.c //
void	display_check();
void 						print_output_nm(int nsyms, int symoff, int stroff, void *ptr);
void						check_seg (struct load_command *com, struct 	mach_header_64 *header);
void 						handle_64 (char *ptr);
void						get_content(uint64_t addr, unsigned int size, char *ptr);
char 	*get_value_otool(uint64_t n_value);
// print.c //

void 						print_archive(void);
void	 					add_archive(void);
void						print_err_munmap(void);
void						print_err_mmap(void);
void						print_err_fstats(void);
void						print_err_open(void);
void						print_nm(void);
void						print_otool(void);
// swap.c //

uint16_t					swap_uint16(uint16_t nb);
uint32_t					swap_uint32(uint32_t nb);
uint64_t					swap_uint64(uint64_t nb);

// get.c //

char 						get_type(uint8_t n_type, t_magic *magic);
char 						*get_value(uint64_t n_value, t_magic *magic);

// get_otool.c // 
char						*get_name(char *name);
int							get_size(char *name);

// tools.c //
t_magic						*lst_reverse(t_magic *root);
int							lst_count(t_magic *lst);
int							lst_count_archive(t_archive *lst);
void						swap(t_magic *node1, t_magic *node2);
void 						sort_alphanumeric(t_magic *head);
void 						sort_alphanumeric_archive(t_archive *node);
char						*itoa_base(int val, int base, int output_size);

// archive.c //
void	handle_archive(char *ptr);
#endif
