#ifndef FRACTOL_H
#define FRACTOL_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./minilibx-linux/mlx.h"

typedef struct s_graph {
    double x_min;
    double x_max;
    double y_min;
    double y_max;
} t_graph;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     max_iter;
    int     color;
    t_graph graph;
} t_mlx;



// utils functions here !

double	ft_atoi(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
void mandelbrot_window();
void julia_window();
int RGB(int i);

#endif