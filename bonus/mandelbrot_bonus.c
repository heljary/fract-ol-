/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:14:04 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 01:55:10 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"
#define HEIGHT 800
#define WIDTH 800

void	calcul_mandelbrot(t_mlx *mlx_mandelbrot, int x, int y)
{
	double (zx_re), (zy_im), (zx), (zy);
	int (iteration), (max_iteration);
	max_iteration = 100;
	while (x < WIDTH)
	{
		mlx_mandelbrot->graph.cx = mlx_mandelbrot->graph.x_min + ((double)x
				/ (double)WIDTH) * (mlx_mandelbrot->graph.x_max
				- mlx_mandelbrot->graph.x_min);
		zx = 0.0;
		zy = 0.0;
		iteration = 0;
		while (zx * zx + zy * zy < 4 && iteration < max_iteration)
		{
			zx_re = zx * zx - zy * zy + mlx_mandelbrot->graph.cx;
			zy_im = 2 * zx * zy + mlx_mandelbrot->graph.cy;
			zx = zx_re;
			zy = zy_im;
			iteration++;
		}
		if (iteration >= max_iteration)
			put_pixel(mlx_mandelbrot, x, y, 0x000000);
		else
			put_pixel(mlx_mandelbrot, x, y, rgb(iteration));
		x++;
	}
}

void	design_mandelbrot(t_mlx *mlx_mandelbrot)
{
	double	x;
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		mlx_mandelbrot->graph.cy = mlx_mandelbrot->graph.y_min + ((double)y
				/ (double)HEIGHT) * (mlx_mandelbrot->graph.y_max
				- mlx_mandelbrot->graph.y_min);
		x = 0;
		calcul_mandelbrot(mlx_mandelbrot, x, y);
		y++;
	}
}

void	mandelbrot_window(void)
{
	t_mlx	mlx_mandelbrot;

	mlx_mandelbrot.graph.x_min = -2.0;
	mlx_mandelbrot.graph.x_max = 2.0;
	mlx_mandelbrot.graph.y_min = -2.0;
	mlx_mandelbrot.graph.y_max = 2.0;
	mlx_mandelbrot.mode = 0;
	mlx_mandelbrot.mlx = mlx_init();
	mlx_mandelbrot.win = mlx_new_window(mlx_mandelbrot.mlx, WIDTH, HEIGHT,
			"Fractol");
	mlx_mandelbrot.img = mlx_new_image(mlx_mandelbrot.mlx, WIDTH, HEIGHT);
	mlx_mandelbrot.addr = mlx_get_data_addr(mlx_mandelbrot.img,
			&mlx_mandelbrot.bpp, &mlx_mandelbrot.line_len,
			&mlx_mandelbrot.endian);
	design_mandelbrot(&mlx_mandelbrot);
	mlx_hook(mlx_mandelbrot.win, 2, 1L << 0, handle_key, &mlx_mandelbrot);
	mlx_mouse_hook(mlx_mandelbrot.win, mouse_hook, &mlx_mandelbrot);
	mlx_put_image_to_window(mlx_mandelbrot.mlx, mlx_mandelbrot.win,
		mlx_mandelbrot.img, 0, 0);
	mlx_hook(mlx_mandelbrot.win, 17, 0, close_window, &mlx_mandelbrot);
	mlx_loop(mlx_mandelbrot.mlx);
}
