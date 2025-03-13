/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic_mandelbrot_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 01:39:12 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 01:54:29 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#define HEIGHT 800
#define WIDTH 800

void	design_color(t_mlx *mlx_cubic_mandelbrot, int iteration, int x, int y)
{
	int	max_iteration;

	max_iteration = 100;
	if (iteration >= max_iteration)
		put_pixel(mlx_cubic_mandelbrot, x, y, 0x000000);
	else
		put_pixel(mlx_cubic_mandelbrot, x, y, rgb(iteration));
}

void	calcul_cubic_mandelbrot(t_mlx *mlx_cubic_mandelbrot, int x, int y)
{
	double (zx_re), (zy_im), (zx), (zy);
	int (iteration), (max_iteration);
	max_iteration = 100;
	while (x < WIDTH)
	{
		mlx_cubic_mandelbrot->graph.cx = mlx_cubic_mandelbrot->graph.x_min
			+ ((double)x / (double)WIDTH) * (mlx_cubic_mandelbrot->graph.x_max
				- mlx_cubic_mandelbrot->graph.x_min);
		zx = 0.0;
		zy = 0.0;
		iteration = 0;
		while (zx * zx + zy * zy < 4 && iteration < max_iteration)
		{
			zx_re = zx * zx * zx - 3 * zx * zy * zy
				+ mlx_cubic_mandelbrot->graph.cx;
			zy_im = 3 * zx * zx * zy - zy * zy * zy
				+ mlx_cubic_mandelbrot->graph.cy;
			zx = zx_re;
			zy = zy_im;
			iteration++;
		}
		design_color(mlx_cubic_mandelbrot, iteration, x, y);
		x++;
	}
}

void	design_cubic_mandelbrot(t_mlx *mlx_cubic_mandelbrot)
{
	double	x;
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		mlx_cubic_mandelbrot->graph.cy = mlx_cubic_mandelbrot->graph.y_min
			+ ((double)y / (double)HEIGHT) * (mlx_cubic_mandelbrot->graph.y_max
				- mlx_cubic_mandelbrot->graph.y_min);
		x = 0;
		calcul_cubic_mandelbrot(mlx_cubic_mandelbrot, x, y);
		y++;
	}
}

void	cubic_mandelbrot_window(void)
{
	t_mlx	mlx_cubic_mandelbrot;

	mlx_cubic_mandelbrot.graph.x_min = -2.0;
	mlx_cubic_mandelbrot.graph.x_max = 2.0;
	mlx_cubic_mandelbrot.graph.y_min = -2.0;
	mlx_cubic_mandelbrot.graph.y_max = 2.0;
	mlx_cubic_mandelbrot.mode = 2;
	mlx_cubic_mandelbrot.mlx = mlx_init();
	mlx_cubic_mandelbrot.win = mlx_new_window(mlx_cubic_mandelbrot.mlx, WIDTH,
			HEIGHT, "Fractol");
	mlx_cubic_mandelbrot.img = mlx_new_image(mlx_cubic_mandelbrot.mlx, WIDTH,
			HEIGHT);
	mlx_cubic_mandelbrot.addr = mlx_get_data_addr(mlx_cubic_mandelbrot.img,
			&mlx_cubic_mandelbrot.bpp, &mlx_cubic_mandelbrot.line_len,
			&mlx_cubic_mandelbrot.endian);
	design_cubic_mandelbrot(&mlx_cubic_mandelbrot);
	mlx_hook(mlx_cubic_mandelbrot.win, 2, 1L << 0, handle_key,
		&mlx_cubic_mandelbrot);
	mlx_mouse_hook(mlx_cubic_mandelbrot.win, mouse_hook, &mlx_cubic_mandelbrot);
	mlx_put_image_to_window(mlx_cubic_mandelbrot.mlx, mlx_cubic_mandelbrot.win,
		mlx_cubic_mandelbrot.img, 0, 0);
	mlx_hook(mlx_cubic_mandelbrot.win, 17, 0, close_window,
		&mlx_cubic_mandelbrot);
	mlx_loop(mlx_cubic_mandelbrot.mlx);
}
