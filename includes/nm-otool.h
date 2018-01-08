

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


// typedef	enum				e_zone_type
// {
// 	TINY,
// 	SMALL,
// 	LARGE
// }							t_zone_type;

// typedef	struct				s_zone
// {
// 	void					*addr;
// 	size_t					nbr_block;
// 	size_t					nbr_block_used;
// 	struct s_zone			*next;
// 	t_zone_type				type;
// 	int						display;
// }							t_zone;

typedef	struct				s_base
{
	char 					*name;
}							t_base;

// delcare function 


void						init_base(void);
t_base						*recover_base(void);

// nm.c //

void 						nm (char *ptr);

// fat.c //

void 						resolve_fat (int ncmds, void *fat_arch);
void 						handle_fat (char *ptr);

// magic.c //

void 						print_output(int nsyms, int symoff, int stroff, void *ptr);
void 						handle_64 (char *ptr);


// swap.c //

uint16_t	swap_uint16(uint16_t nb);
uint32_t	swap_uint32(uint32_t nb);
uint64_t	swap_uint64(uint64_t nb);
#endif
