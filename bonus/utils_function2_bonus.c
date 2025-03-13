/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 01:32:06 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 01:56:21 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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
	double (mouse_re), (mouse_im), (zoom);
	if (!mlx_w || (button != 4 && button != 5))
		return (0);
	mouse_re = mlx_w->graph.x_min + ((double)x / WIDTH) * (mlx_w->graph.x_max
			- mlx_w->graph.x_min);
	mouse_im = mlx_w->graph.y_min + ((double)y / HEIGHT) * (mlx_w->graph.y_max
			- mlx_w->graph.y_min);
	if (button == 4)
		zoom = 0.8;
	else if (button == 5)
		zoom = 1.25;
	mlx_w->graph.x_min = mouse_re + (mlx_w->graph.x_min - mouse_re) * zoom;
	mlx_w->graph.x_max = mouse_re + (mlx_w->graph.x_max - mouse_re) * zoom;
	mlx_w->graph.y_min = mouse_im + (mlx_w->graph.y_min - mouse_im) * zoom;
	mlx_w->graph.y_max = mouse_im + (mlx_w->graph.y_max - mouse_im) * zoom;
	if (mlx_w->mode == 0)
		design_mandelbrot(mlx_w);
	else if (mlx_w->mode == 1)
		design_julia(mlx_w);
	else
		design_cubic_mandelbrot(mlx_w);
	mlx_put_image_to_window(mlx_w->mlx, mlx_w->win, mlx_w->img, 0, 0);
	return (0);
}

void	func_norm(int keycode, t_mlx *mlx_d, double x_range, double y_range)
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
	func_norm(keycode, mlx_d, x_range, y_range);
	if (mlx_d->mode == 0)
		design_mandelbrot(mlx_d);
	else if (mlx_d->mode == 1)
		design_julia(mlx_d);
	else
		design_cubic_mandelbrot(mlx_d);
	mlx_put_image_to_window(mlx_d->mlx, mlx_d->win, mlx_d->img, 0, 0);
	return (0);
}
