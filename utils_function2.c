/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:22:54 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 03:11:37 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define HEIGHT 900
#define WIDTH 800

void	put_pixel(t_mlx *mlx_s, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	offset = (y * mlx_s->line_len) + (x * (mlx_s->bpp / 8));
	*(int *)(mlx_s->addr + offset) = color;
}

int	close_window(t_mlx *mlx_w)
{
	mlx_destroy_image(mlx_w->mlx, mlx_w->img);
	mlx_destroy_window(mlx_w->mlx, mlx_w->win);
	mlx_destroy_display(mlx_w->mlx);
	free(mlx_w->mlx);
	exit(0);
}

int	mouse_hook(int button, int x, int y, t_mlx *mlx_w)
{
	double		zoom;

	(void)x;
	(void)y;
	if (!mlx_w)
		return (0);
	if (button == 4)
		zoom = 0.8;
	else if (button == 5)
		zoom = 1.25;
	mlx_w->graph.x_min *= zoom;
	mlx_w->graph.x_max *= zoom;
	mlx_w->graph.y_min *= zoom;
	mlx_w->graph.y_max *= zoom;
	if (mlx_w->mode == 0)
		design_mandelbrot(mlx_w);
	else
		design_julia(mlx_w);
	mlx_put_image_to_window(mlx_w->mlx, mlx_w->win, mlx_w->img, 0, 0);
	return (0);
}

void	func_keymove(int keycode, t_mlx *mlx_d, double x_range, double y_range)
{
	double	move;

	move = 0.1;
	if (keycode == 65362)
	{
		mlx_d->graph.y_min -= y_range * move;
		mlx_d->graph.y_max -= y_range * move;
	}
	else if (keycode == 65364)
	{
		mlx_d->graph.y_min += y_range * move;
		mlx_d->graph.y_max += y_range * move;
	}
	else if (keycode == 65361)
	{
		mlx_d->graph.x_min -= x_range * move;
		mlx_d->graph.x_max -= x_range * move;
	}
	else if (keycode == 65363)
	{
		mlx_d->graph.x_min += x_range * move;
		mlx_d->graph.x_max += x_range * move;
	}
	else if (keycode == 65307)
		close_window(mlx_d);
}

int	handle_key(int keycode, t_mlx *mlx_d)
{
	double	x_range;
	double	y_range;

	x_range = mlx_d->graph.x_max - mlx_d->graph.x_min;
	y_range = mlx_d->graph.y_max - mlx_d->graph.y_min;
	func_keymove(keycode, mlx_d, x_range, y_range);
	if (mlx_d->mode == 0)
		design_mandelbrot(mlx_d);
	else
		design_julia(mlx_d);
	mlx_put_image_to_window(mlx_d->mlx, mlx_d->win, mlx_d->img, 0, 0);
	return (0);
}
