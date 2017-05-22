/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:56:50 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 20:52:51 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_spheres(t_object *sph1, t_object *sph2)
{
	sph1->type = 1;
	sph1->pos.x = 390;
	sph1->pos.y = 320;
	sph1->pos.z = 410;
	sph1->radius = 100;
	sph1->diffuse[0] = .0;
	sph1->diffuse[1] = .0;
	sph1->diffuse[2] = .5;
	sph1->reflection = 0;
	sph2->type = 1;
	sph2->pos.x = 700;
	sph2->pos.y = 400;
	sph2->pos.z = 810;
	sph2->radius = 180;
	sph2->diffuse[0] = 1;
	sph2->diffuse[1] = 1;
	sph2->diffuse[2] = 1;
	sph2->reflection = 0;
}

void	init_planes(t_object *pl1, t_object *pl2)
{
	pl1->type = 2;
	pl1->pos.x = 0;
	pl1->pos.y = 0;
	pl1->pos.z = 1990;
	pl1->diffuse[0] = 1.0;
	pl1->diffuse[1] = .0;
	pl1->diffuse[2] = .0;
	pl1->reflection = 0;
	pl1->n.x = 0;
	pl1->n.y = 0;
	pl1->n.z = -1;
	pl2->type = 2;
	pl2->pos.x = 0;
	pl2->pos.y = 600;
	pl2->pos.z = 800;
	pl2->diffuse[0] = .0;
	pl2->diffuse[1] = 1.0;
	pl2->diffuse[2] = .0;
	pl2->reflection = 0;
	pl2->n.x = 0;
	pl2->n.y = -4;
	pl2->n.z = -0.5;
}

void	init_cylinder(t_object *cl1)
{
	cl1->type = 3;
	cl1->pos.x = 300;
	cl1->pos.y = 200;
	cl1->pos.z = 1000;
	cl1->direct.x = 0;
	cl1->direct.y = 1;
	cl1->direct.z = 0;
	cl1->radius = 90;
	cl1->diffuse[0] = 1.0;
	cl1->diffuse[1] = .0;
	cl1->diffuse[2] = .0;
	cl1->reflection = 0;
}

void	init_cone(t_object *cn1)
{
	cn1->type = 4;
	cn1->pos.x = 600;
	cn1->pos.y = 200;
	cn1->pos.z = 400;
	cn1->direct.x = 0;
	cn1->direct.y = 1;
	cn1->direct.z = 0;
	cn1->radius = 20;
	cn1->k = .2679492;
	cn1->diffuse[0] = 1.0;
	cn1->diffuse[1] = .50;
	cn1->diffuse[2] = .50;
	cn1->reflection = 0;
}

void	wininit(t_win *win)
{
	win->width = 1000;
	win->height = 800;
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, win->width, win->height, "RTv1");
	init_spheres(&win->object[0], &win->object[1]);
	init_planes(&win->object[2], &win->object[3]);
	init_cylinder(&win->object[4]);
	init_cone(&win->object[5]);
	init_lights(&win->light[0], 100, 100, -310);
	init_lights(&win->light[1], 900, 600, -510);
	win->sx = 0;
	win->sy = 0;
	win->dx = 0;
	win->dy = 0;
	win->dz = 0;
}
