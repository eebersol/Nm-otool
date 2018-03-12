/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:37:41 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:42 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_color	*ft_create_color_rgb(int r, int g, int b)
{
	t_color *color;

	color = (t_color *)malloc(sizeof(color));
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

t_color	*ft_create_color_hex(int hex_color)
{
	t_color *color;

	color = (t_color *)malloc(sizeof(color));
	color->r = ((hex_color >> 16) & 0xFF) / 255;
	color->g = ((hex_color >> 8) & 0xFF) / 255;
	color->b = (hex_color & 0xFF) / 255;
	return (color);
}
