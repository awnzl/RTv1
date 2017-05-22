/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:55:19 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 16:51:41 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** фактически	v_mod => sqrtf(v_dot(direct, direct))
*/

double		v_mod(t_vector *direct)
{
	return (sqrtf(direct->x * direct->x + direct->y * direct->y +
				direct->z * direct->z));
}

/*
** Здесь использован v_mod => sqrtf(v_dot(direct, direct))
** не знаю пока, нужен ли он еще где, потому функцию выше оставли
** v_unit => normalize в OpenGL - приводит существующий вектор к единичному
*/

t_vector	v_unit(t_vector *direct)
{
	t_vector	res;
	double		vmod;

	vmod = sqrtf(direct->x * direct->x + direct->y * direct->y +
				direct->z * direct->z);
	res.x = direct->x / vmod;
	res.y = direct->y / vmod;
	res.z = direct->z / vmod;
	return (res);
}

void		ray_init(t_ray *r, int x, int y, t_win *w)
{
	r->start.x = x + w->sx;
	r->start.y = y + w->sy;
	r->start.z = -1000;
	r->direct.x = 0 + w->dx;
	r->direct.y = 0 + w->dy;
	r->direct.z = 1 + w->dx + w->dy;
	r->direct = v_unit(&r->direct);
}

/*
** m = D|V*t + X|V
** X => O-C => v_sub(&r->start, &obj->pos);
*/

t_vector	get_normal(t_vector *ns, t_object *obj)
{
	t_vector	res;
	t_vector	a;
	t_vector	b;

	res = obj->n;
	if (obj->type == 1)
		res = v_sub(ns, &obj->pos);
	else if (obj->type == 3)
	{
		b = v_sub(ns, &obj->pos);
		a = v_scale(v_dot(&b, &obj->direct), &obj->direct);
		res = v_sub(&b, &a);
	}
	else if (obj->type == 4)
	{
		a = v_sub(ns, &obj->pos);
		b = v_scale((1 + obj->k * obj->k) * v_dot(&a, &obj->direct),
				&obj->direct);
		res = v_sub(&a, &b);
	}
	return (res);
}

void		ray_trace(int x, int y, t_win *win)
{
	t_ray	r;
	t_color	col;
	int		level;
	double	coef;
	double	rgb[3];

	ray_init(&r, x, y, win);
	col.color = 0;
	level = -1;
	coef = 1.0;
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	while (coef > .0 && ++level < 8)
	{
		if (!inwhile(rgb, &coef, &r, win))
			break ;
	}
	col.c[2] = (unsigned char)MIN(rgb[2] * 255.0f, 255.0f);
	col.c[1] = (unsigned char)MIN(rgb[1] * 255.0f, 255.0f);
	col.c[0] = (unsigned char)MIN(rgb[0] * 255.0f, 255.0f);
	win->imdat[(x + y * win->width)] = col.color;
}
