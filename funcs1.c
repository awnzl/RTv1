/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avenzel <avenzel@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 14:21:45 by avenzel           #+#    #+#             */
/*   Updated: 2017/05/22 16:29:23 by avenzel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		exit_buttons(void)
{
	exit(1);
	return (0);
}

int		key_hook(int kc, t_win *w)
{
	if (kc == 53 || kc == 65307)
		exit(0);
	else if (kc == 124)
	{
		w->dx += (w->dx > 1) ? 0 : .01;
		put_image(w);
	}
	else if (kc == 123)
	{
		w->dx += (w->dx < -1) ? 0 : -.01;
		put_image(w);
	}
	else if (kc == 125)
	{
		w->dy += (w->dy > 1) ? 0 : .01;
		put_image(w);
	}
	else if (kc == 126)
	{
		w->dy += (w->dy < -1) ? 0 : -.01;
		put_image(w);
	}
	return (0);
}

void	*thfun(void *v)
{
	int				x;
	int				y;
	int				lim;
	t_forthreads	*thread_container;

	thread_container = (t_forthreads*)v;
	y = (thread_container->y == 0) ? -1 : thread_container->y - 1;
	lim = thread_container->w->height / 4 + thread_container->y;
	while (++y < lim)
	{
		x = -1;
		while (++x < thread_container->w->width)
			ray_trace(x, y, thread_container->w);
	}
	pthread_exit(NULL);
}

void	threads_manage(t_win *w)
{
	int				i;
	t_forthreads	thread_container[4];

	i = -1;
	while (++i < 4)
	{
		thread_container[i].w = w;
		thread_container[i].y = i * w->height / 4;
		pthread_create(&thread_container[i].thread_id, NULL,
				&thfun, (void*)&thread_container[i]);
	}
	while (i--)
		pthread_join(thread_container[i].thread_id, NULL);
}

void	put_image(t_win *w)
{
	w->img = mlx_new_image(w->mlx, w->width, w->height);
	w->imgaddr = mlx_get_data_addr(w->img, &w->bspp, &w->ls,
			&w->endian);
	w->imdat = (int*)w->imgaddr;
	threads_manage(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
	mlx_destroy_image(w->mlx, w->img);
	mlx_hook(w->win, 17, 0, exit_buttons, w);
	mlx_key_hook(w->win, &key_hook, w);
}
