/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:21:20 by heljary           #+#    #+#             */
/*   Updated: 2025/03/12 15:20:49 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_graph
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	cy;
	double	cx;
}			t_graph;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		max_iter;
	int		color;
	int		mode;
	t_graph	graph;
}			t_mlx;

// utils functions here !

double		ft_atoi(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		put_pixel(t_mlx *mlx_s, int x, int y, int color);
void		mandelbrot_window(void);
void		julia_window(double cx, double cy);
int			handle_key(int keycode, t_mlx *mlx_w);
int			mouse_hook(int button, int x, int y, t_mlx *mlx_w);
int			close_window(t_mlx *mlx_w);
void		design_mandelbrot(t_mlx *mlx_mandelbrot);
void		design_julia(t_mlx *mlx_w);
size_t		ft_strlen(const char *str);
int			rgb(int i);

#endif