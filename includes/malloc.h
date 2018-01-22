/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:20:05 by eebersol          #+#    #+#             */
/*   Updated: 2017/09/28 15:23:48 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <string.h>

# define TINY_BLOCK			1024
# define SMALL_BLOCK		PAGE_SIZE * 16
# define FLAG_PROT			PROT_WRITE | PROT_READ
# define FLAG_MAP			MAP_ANON | MAP_PRIVATE
# define PAGE_SIZE			getpagesize()

typedef	enum				e_zone_type
{
	TINY,
	SMALL,
	LARGE
}							t_zone_type;

typedef	struct				s_zone
{
	void					*addr;
	size_t					nbr_block;
	size_t					nbr_block_used;
	struct s_zone			*next;
	t_zone_type				type;
	int						display;
}							t_zone;

typedef	struct				s_base
{
	void					*realloc_src;
	int						realloc_size;
	int						realloc_new_zone;
	int						is_realloc;
	t_zone_type				realloc_type;
	t_zone_type				type;
	t_zone					*memory;
}							t_base;

void						*find_place(t_base *base,
								t_zone *zone, size_t size);
void						*malloc_memcpy(void *dst,
								const void *src, size_t n);
t_zone						*get_last_zone(t_zone *zone,
								t_base *base, size_t size);
void						*malloc(size_t size);
void						del_zone(t_zone **zone,
								int at, int block_size, int nbr_block);
t_zone						*browse_zone(t_zone *zone);
void						verify_zone(t_base *base);
void						check_zone(t_zone *zone, void *ptr);
void						free(void *ptr);
void						*modify_base(void *ptr, size_t new_size);
void						*browse_zones_realloc(t_zone *zone,
								void *old_ptr, size_t new_size, void *new_ptr);
void						*inspect_zone(t_zone *zone,
								void *ptr, void *old_ptr, size_t new_size);
void						*find_old_alloc(t_base *base,
								void *ptr, size_t new_size);
void						*realloc(void *ptr, size_t size);
void						printf_info_zone(void *ptr,
								int i, t_zone_type type);
void						print_info_block(void *ptr, int i, int size);
size_t						display_block(t_zone *zone);
int							print_zone(t_zone *zone);
void						show_alloc_mem(void);
void						*smap(size_t len);
t_zone						*fix_zone_size(size_t size_total, size_t size);
t_zone						*create_zone(size_t size);
int							count_len_zone(t_zone *zone);
t_zone						*get_zone(void);
t_zone_type					get_type(size_t size);
size_t						get_size_type(t_zone_type type);
size_t						get_size_zone(t_zone_type type, size_t size);
size_t						get_nbr_block(size_t size);
void						init_base(void);
t_base						*recover_base(void);
void						ft_putnbr(int n);
void						ft_putstr(char *str);
char						*ft_itohex(void *ptr);
void						ft_lst_bubble_sort(t_zone *node);
void						ft_lst_swap(t_zone *node1, t_zone *node2);
size_t						ft_strlen(const char *s);

#endif