


nm liste les symboles provenant des fichiers objets fichier-objet... Si aucun fichier objet n'est fourni comme argument, nm suppose qu'on lui a spécifié le fichier a.out.


- Si aucun argument passer a nm, il prend le a.out si il y en a un.








valeurs des symboles					  types								noms1
		0000000a							T							global_function
		00000025							T							global_function2
		00000004							C							global_var
		00000000							D							global_var_init
		00000004							b							local_static_var.1255
		00000008							d							local_static_var_init.1256
		0000003b							T							main
		00000036							T							non_mangled_function
		00000000							t							static_function
		00000000							b							static_var
		00000004							d 							static_var_init


                 U _create_zone
0000000000000000 T _find_place
                 U _ft_strlen
0000000000000150 T _get_last_zone
                 U _get_size_type
                 U _get_type
00000000000001b0 T _malloc
00000000000000f0 T _malloc_memcpy
                 U _recover_base







 Swapping for resolve_fat need to swap_uint32 all value




#include "nm_otool.h"

uint16_t	swap_uint16(uint16_t nb)
{
	nb = (nb << 8) | (nb >> 8);
	return (nb);
}

uint32_t	swap_uint32(uint32_t nb)
{
	nb = ((nb & 0x000000FF) << 24 |
				(nb & 0x0000FF00) << 8 |
				(nb & 0x00FF0000) >> 8 |
				(nb & 0xFF000000) >> 24);
	return (nb);
}

uint64_t	swap_uint64(uint64_t nb)
{
	nb = ((nb & 0x00000000000000FF) << 56 |
				(nb & 0x000000000000FF00) << 40 |
				(nb & 0x0000000000FF0000) << 24 |
				(nb & 0x00000000FF000000) << 8 |
				(nb & 0x000000FF00000000) >> 8 |
				(nb & 0x0000FF0000000000) >> 24 |
				(nb & 0x00FF000000000000) >> 40 |
				(nb & 0xFF00000000000000) >> 56);
	return (nb);
}