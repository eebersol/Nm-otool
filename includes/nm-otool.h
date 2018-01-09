

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
	char					*value;
	struct s_magic			*next;
}							t_magic;

typedef	struct				s_base
{
	char 					*name;
	t_magic 				*magicBase;
}							t_base;

// delcare function 


void						init_base(void);
t_base						*recover_base(void);

// nm.c //

void 						nm (char *ptr);

// fat.c //

void 						resolve_fat (int ncmds, struct 	fat_arch *fat_arch, int i);
void 						handle_fat (char *ptr);

// magic.c //

void 						print_output(int nsyms, int symoff, int stroff, void *ptr);
void 						handle_64 (char *ptr);

// print.c //

void						printf_prg_name();
void						print_handle_64();

// swap.c //

uint16_t					swap_uint16(uint16_t nb);
uint32_t					swap_uint32(uint32_t nb);
uint64_t					swap_uint64(uint64_t nb);

// get.c //

char 						get_type(uint8_t n_type);
char 						*get_value(uint64_t n_value, char type);

// tools.c //
void						*smap(size_t len);
int							lst_count(t_magic *lst);
t_magic						*sort_list_alpha(t_magic *magic);
t_magic						*swapNode(t_magic *magic);
void 						pairWiseSwap(t_magic *head);
void						swap(t_magic *node1, t_magic *node2);
#endif
