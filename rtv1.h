/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 14:18:52 by avenzel           #+#    #+#             */
/*   Updated: 2017/12/06 14:16:05 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RTV1_H
# define __RTV1_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <unistd.h>

# include "mlx.h"

# define OBJECTS 6
# define LIGHTS 2
# define MIN(a, b) (a < b ? a : b)
# define MAX(a, b) (a < b ? b : a)

typedef union	u_color
{
	int			color;
	char		c[4];
}				t_color;

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	direct;
	t_vector	start;
}				t_ray;

typedef struct	s_light
{
	t_vector	pos;
	double		intensity[3];
}				t_light;

/*
**	reflection and diffuse - it's about material
**  type: 1 - sphere, 2 - plane, 3 - cylinder, 4 - cone
*/

typedef struct	s_object
{
	int			type;

	t_vector	pos;
	t_vector	direct;
	t_vector	n;
	double		radius;
	double		k;
	double		diffuse[3];
	double		reflection;
}				t_object;

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*imgaddr;
	int			*imdat;
	int			bspp;
	int			ls;
	int			endian;
	int			width;
	int			height;
	double		sx;
	double		sy;
	double		dx;
	double		dy;
	double		dz;
	t_object	object[OBJECTS];
	t_light		light[LIGHTS];
}				t_win;

typedef struct	s_container
{
	t_win		*w;
	int			y;
	pthread_t	thread_id;
}				t_forthreads;

void			wininit(t_win *win);
void			init_lights(t_light *l, int x, int y, int z);
void			put_image(t_win *win);
void			ray_trace(int x, int y, t_win *win);

t_vector		v_add(t_vector *v1, t_vector *v2);
t_vector		v_sub(t_vector *v1, t_vector *v2);
t_vector		v_mult(t_vector *v1, t_vector *v2);
t_vector		v_scale(double n, t_vector *v);
t_vector		v_unit(t_vector *direct);
t_vector		get_normal(t_vector *ns, t_object *obj);

double			v_dot(t_vector *v1, t_vector *v2);
double			v_mod(t_vector *direct);

double			intersect_sphere(t_ray *r, t_object *s, double *nearest_t);
double			intersect_plane(t_ray *r, t_object *p, double *nearest_t);
int				intersect_object(t_ray *r, t_object *o, double *nearest_t);
int				inwhile(double *rgb, double *coef, t_ray *r, t_win *win);

#endif
