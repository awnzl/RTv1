/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_funcs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:25:10 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 13:58:35 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** newstart => P (точка пересечения луча с поверхностью)
*/

int		check_objects_intersect(t_ray *r, t_vector *ns, t_vector *n, t_win *win)
{
	double		t;
	double		temp;
	int			i;
	int			obj;
	t_vector	scaled;

	t = 20000.0;
	obj = -1;
	i = -1;
	while (++i < OBJECTS)
		if (intersect_object(r, &win->object[i], &t))
			obj = i;
	if (obj == -1)
		return (-1);
	scaled = v_scale(t, &r->direct);
	*ns = v_add(&r->start, &scaled);
	*n = get_normal(ns, &win->object[obj]);
	temp = v_dot(n, n);
	if (temp == 0)
		return (-1);
	temp = 1.0f / sqrtf(temp);
	*n = v_scale(temp, n);
	return (obj);
}

int		calc_shadows(double t, t_ray *lightray, t_win *win)
{
	int		i;
	int		inshadow;

	i = -1;
	inshadow = 0;
	while (++i < OBJECTS)
		if (intersect_object(lightray, &win->object[i], &t))
		{
			inshadow = 1;
			break ;
		}
	return (inshadow);
}

void	calc_pix_color(double *rgb, double lambert, double *intensity,
		double *diffuse)
{
	lambert = lambert + pow(lambert, 256);
	rgb[2] += lambert * intensity[2] * diffuse[2];
	rgb[1] += lambert * intensity[1] * diffuse[1];
	rgb[0] += lambert * intensity[0] * diffuse[0];
}

void	find_light_value(double *rgb, int obj, t_vector *nsn, t_win *win)
{
	int			i;
	int			inshadow;
	double		t;
	t_vector	dist;
	t_ray		lightray;

	i = -1;
	while (++i < LIGHTS)
	{
		dist = v_sub(&win->light[i].pos, &nsn[0]);
		if (v_dot(&nsn[1], &dist) <= 0.0f)
			continue ;
		t = sqrtf(v_dot(&dist, &dist));
		if (t <= 0.0f)
			continue ;
		lightray.start = nsn[0];
		lightray.direct = v_scale((1 / t), &dist);
		inshadow = calc_shadows(t, &lightray, win);
		if (!inshadow)
			calc_pix_color(rgb, v_dot(&lightray.direct, &nsn[1]),
					win->light[i].intensity, win->object[obj].diffuse);
	}
}

int		inwhile(double *rgb, double *coef, t_ray *r, t_win *win)
{
	t_vector	n;
	t_vector	newstart;
	t_vector	container[2];
	int			obj;

	if ((obj = check_objects_intersect(r, &newstart, &n, win)) < 0)
		return (0);
	container[0] = newstart;
	container[1] = n;
	find_light_value(rgb, obj, container, win);
	(*coef) *= win->object[obj].reflection;
	return (1);
}
