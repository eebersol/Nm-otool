/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eebersol <eebersol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 12:59:26 by eebersol          #+#    #+#             */
/*   Updated: 2018/03/12 10:53:25 by eebersol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRIX_H
# define FT_MATRIX_H

typedef struct	s_matrix {
	double		a1;
	double		a2;
	double		a3;
	double		a4;
	double		b1;
	double		b2;
	double		b3;
	double		b4;
	double		c1;
	double		c2;
	double		c3;
	double		c4;
	double		d1;
	double		d2;
	double		d3;
	double		d4;
}				t_matrix;

t_matrix		*ft_matrix_rotate_x(double beta);
t_matrix		*ft_matrix_rotate_y(double beta);
t_matrix		*ft_matrix_rotate_z(double beta);
t_matrix		*ft_matrix_translate(double tx, double ty, double tz);
t_matrix		*ft_matrix_scale(double scale);

#endif
