/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_funcs3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:28:22 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 18:58:48 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		cylinder_discr(t_ray *r, t_object *c, double *b)
{
	t_vector	tmp;
	t_vector	resva;
	t_vector	bres;
	t_vector	cp;

	tmp = v_scale(v_dot(&r->direct, &c->direct), &c->direct);
	resva = v_sub(&r->direct, &tmp);
	cp = v_sub(&r->start, &c->pos);
	tmp = v_scale(v_dot(&cp, &c->direct), &c->direct);
	bres = v_sub(&cp, &tmp);
	*b = 2 * v_dot(&resva, &bres);
	return ((*b) * (*b) - 4.0 * v_dot(&resva, &resva) *
		(v_dot(&bres, &bres) - c->radius * c->radius));
}

/*
** cylindrader
**
** double A = vectorDot(&r->dir, &r->dir);
** vector dist = vectorSub(&r->start, &s->pos);
** double b = 2 * vectorDot(&r->dir, &dist);
** double C = vectorDot(&dist, &dist) - (s->radius * s->radius);
** double discr = b * b - 4 * A * C;
** double sqrtdiscr = sqrtf(discr);
** double t0 = (-b + sqrtdiscr)/(2);
** double t1 = (-b - sqrtdiscr)/(2);
**
** c => r->start (E)
** b => r->direct (D)
** va => c->direct
** pa => c->pos
** A = (b - (b,va)va)^2;
** (b,va) => nv =  v_dot(&b, &va);
** nvva => scv = v_scale(nv, &va);
** (b - scv)^2 => resv = v_sub(&b, &scv);
** A => v_dot(&resv, &resv);
*/

double		intersect_cylinder(t_ray *r, t_object *c, double *nearest_t)
{
	double		b;
	double		discr;
	double		sqrtdiscr;
	double		t[2];

	c->direct = v_unit(&c->direct);
	discr = cylinder_discr(r, c, &b);
	if (discr >= 0)
	{
		sqrtdiscr = sqrtf(discr);
		t[0] = (-b + sqrtdiscr) / 2.;
		t[1] = (-b - sqrtdiscr) / 2.;
		if (t[0] > t[1])
			t[0] = t[1];
		if ((t[0] > 0.001f) && (t[0] <= *nearest_t))
		{
			*nearest_t = t[0];
			return (1);
		}
	}
	return (0);
}

double		cone_discr(t_ray *r, t_object *cn, double *b)
{
	double		a;
	double		c;
	double		ang;
	t_vector	tmp1;

	cn->direct = v_unit(&cn->direct);
	ang = 1 + cn->k * cn->k;
	tmp1 = v_sub(&r->start, &cn->pos);
	a = v_dot(&r->direct, &r->direct) - ang * v_dot(&r->direct, &cn->direct) *
		v_dot(&r->direct, &cn->direct);
	*b = 2 * (v_dot(&r->direct, &tmp1) - ang * v_dot(&r->direct, &cn->direct) *
			v_dot(&tmp1, &cn->direct));
	c = v_dot(&tmp1, &tmp1) - ang * v_dot(&tmp1, &cn->direct) *
		v_dot(&tmp1, &cn->direct);
	return ((*b) * (*b) - 4 * a * c);
}

/*
** C - pos?
** V - cn->direct;
** k - tangent of half angle of the cone
** D - r->direct;
** a = D|D - (1+k*k)*((D|V)^2)
** b/2 = D|X  - (1+k*k)*(D|V)*(X|V)
** c = X|X - (1+k*k)*((X|V)^2)
** X => O-C => v_sub(&r->start, &s->pos);
*/

double		intersect_cone(t_ray *r, t_object *cn, double *nearest_t)
{
	double		b;
	double		discr;
	double		t[2];

	discr = cone_discr(r, cn, &b);
	if (discr >= 0)
	{
		discr = sqrtf(discr);
		t[0] = (-b + discr) / (2);
		t[1] = (-b - discr) / (2);
		if (t[0] > t[1])
			t[0] = t[1];
		if ((t[0] > 0.001f) && (t[0] <= *nearest_t))
		{
			*nearest_t = t[0];
			return (1);
		}
	}
	return (0);
}

int			intersect_object(t_ray *r, t_object *o, double *nearest_t)
{
	if (o->type == 1)
		return (intersect_sphere(r, o, nearest_t));
	else if (o->type == 2)
		return (intersect_plane(r, o, nearest_t));
	else if (o->type == 3)
		return (intersect_cylinder(r, o, nearest_t));
	else if (o->type == 4)
		return (intersect_cone(r, o, nearest_t));
	return (0);
}
