/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 14:17:38 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 14:00:45 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** x y - положение относительно координат экрана, а минус z - удаление от
** плоскости (центра координат)
*/

void		init_lights(t_light *li, int x, int y, int z)
{
	li->pos.x = x;
	li->pos.y = y;
	li->pos.z = z * 10;
	li->intensity[0] = .5;
	li->intensity[1] = .5;
	li->intensity[2] = .5;
}

/*
** C => s->pos;
** r => s->radius;
** O => r->start;
** D => r->direct;
** P => ray => O + Dt;
** P-C => Dt + X;
** X => O-C => v_sub(&r->start, &s->pos);
** nrm(P-C) => V/(sqrt(v_dot(&V, &V)));
*/

double		intersect_sphere(t_ray *r, t_object *s, double *nearest_t)
{
	t_vector	distance;
	double		b;
	double		discr;
	double		t[2];

	distance = v_sub(&r->start, &s->pos);
	b = 2 * v_dot(&r->direct, &distance);
	discr = b * b - 4 * v_dot(&r->direct, &r->direct) *
		(v_dot(&distance, &distance) - (s->radius * s->radius));
	if (discr >= 0)
	{
		discr = sqrtf(discr);
		t[0] = (-b + discr) / 2;
		t[1] = (-b - discr) / 2;
		if (t[0] > t[1])
			t[0] = t[1];
		if ((t[0] > 0.001f) && (t[0] < *nearest_t))
		{
			*nearest_t = t[0];
			return (1);
		}
	}
	return (0);
}

/*
** t = -X|V / D/V
** V = normal => p->n
** D => r->direct
** X => v_sub(&r->start, &p->pos);
*/

double		intersect_plane(t_ray *r, t_object *p, double *nearest_t)
{
	double		t;
	double		nd;
	t_vector	tmpv;

	p->n = v_unit(&p->n);
	nd = v_dot(&p->n, &r->direct);
	if (nd != 0)
	{
		tmpv = v_sub(&p->pos, &r->start);
		t = v_dot(&p->n, &tmpv) / nd;
		if (t > 0.001f && t < *nearest_t)
		{
			*nearest_t = t;
			return (1);
		}
	}
	return (0);
}

int			main(void)
{
	t_win	win;

	wininit(&win);
	put_image(&win);
	mlx_loop(win.mlx);
	return (0);
}
