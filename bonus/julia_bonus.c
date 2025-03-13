/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:13:48 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 01:54:59 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#define HEIGHT 900
#define WIDTH 800

void	calcul_julia(t_mlx *mlx_julia, int x, int y)
{
	double (zx_re), (zy_im), (zx), (zy);
	int (iteration), (max_iteration);
	max_iteration = 100;
	while (x < WIDTH)
	{
		zx = mlx_julia->graph.x_min + ((double)x / (double)WIDTH)
			* (mlx_julia->graph.x_max - mlx_julia->graph.x_min);
		zy = mlx_julia->graph.y_min + ((double)y / (double)HEIGHT)
			* (mlx_julia->graph.y_max - mlx_julia->graph.y_min);
		iteration = 0;
		while (zx * zx + zy * zy < 4 && iteration < max_iteration)
		{
			zx_re = zx * zx - zy * zy + mlx_julia->graph.cx;
			zy_im = 2 * zx * zy + mlx_julia->graph.cy;
			zx = zx_re;
			zy = zy_im;
			iteration++;
		}
		if (iteration == max_iteration)
			put_pixel(mlx_julia, x, y, 0x000000);
		else
			put_pixel(mlx_julia, x, y, rgb(iteration));
		x++;
	}
}

void	design_julia(t_mlx *mlx_julia)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		calcul_julia(mlx_julia, x, y);
		y++;
	}
}

void	julia_window(double cx, double cy)
{
	t_mlx	mlx_julia;

	mlx_julia.graph.x_min = -2.0;
	mlx_julia.graph.x_max = 2.0;
	mlx_julia.graph.y_min = -2.0;
	mlx_julia.graph.y_max = 2.0;
	mlx_julia.graph.cy = cy;
	mlx_julia.graph.cx = cx;
	mlx_julia.mode = 1;
	mlx_julia.mlx = mlx_init();
	mlx_julia.win = mlx_new_window(mlx_julia.mlx, WIDTH, HEIGHT, "Fractol");
	mlx_julia.img = mlx_new_image(mlx_julia.mlx, WIDTH, HEIGHT);
	mlx_julia.addr = mlx_get_data_addr(mlx_julia.img, &mlx_julia.bpp,
			&mlx_julia.line_len, &mlx_julia.endian);
	design_julia(&mlx_julia);
	mlx_hook(mlx_julia.win, 2, 1L << 0, handle_key, &mlx_julia);
	mlx_mouse_hook(mlx_julia.win, mouse_hook, &mlx_julia);
	mlx_put_image_to_window(mlx_julia.mlx, mlx_julia.win, mlx_julia.img, 0, 0);
	mlx_hook(mlx_julia.win, 17, 0, close_window, &mlx_julia);
	mlx_loop(mlx_julia.mlx);
	close_window(&mlx_julia);
}
