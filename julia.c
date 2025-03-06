/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:13:48 by heljary           #+#    #+#             */
/*   Updated: 2025/03/06 02:50:59 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define height  900
#define width   800


void mlx_put(t_mlx *mlx_j, int x, int y, int color)
{
    int offset;
    if (x < 0 || y < 0  || x >= width || y >= height)
        return;
    offset = (y * mlx_j -> line_len) + (x * (mlx_j -> bpp/8));
    *(int *)(mlx_j -> addr + offset) = color;
}

void design_julia(t_mlx mlx_w,double cx,double cy)
{
    double zx_next;
    double zy_next;
    
    double zx;
    double zy;

    int x;
    int y = 0;
     
    int iteration;
    int max_iteration = 100;
    while(y < height)
    {
        x = 0;
        while (x < width)
        {
            zx = mlx_w.graph.x_min + (x / (double)width) * (mlx_w.graph.x_max - mlx_w.graph.x_min);
            zy = mlx_w.graph.x_min + (y / (double)height) * (mlx_w.graph.y_max - mlx_w.graph.y_min);
            iteration = 0;
            while(zx * zx + zy * zy < 4 && iteration < max_iteration)
            {
                zx_next = zx * zx - zy * zy + cx;
                zy_next = 2 * zx * zy + cy;

                zx = zx_next;
                zy = zy_next;
                iteration ++;
            }
            if(iteration == max_iteration)
            {
                mlx_put(&mlx_w,x,y,0x000000);
            }else
                mlx_put(&mlx_w,x,y,RGB(iteration));
            x++;
        }
        y++;
    }
}

void julia_window(double cx,double cy)
{
    t_mlx mlx_w;
    mlx_w.graph.x_min = -2.0;
    mlx_w.graph.x_max = 2.0;
    mlx_w.graph.y_min = -2.0;
    mlx_w.graph.y_max = 2.0;
    mlx_w.mlx = mlx_init();
    mlx_w.win =  mlx_new_window(mlx_w.mlx,width, height,"Fractol");
    mlx_w.img = mlx_new_image(mlx_w.mlx,width, height);
    mlx_w.addr = mlx_get_data_addr(mlx_w.img,&mlx_w.bpp,&mlx_w.line_len,&mlx_w.endian);
    design_julia(mlx_w,cx,cy);
    mlx_put_image_to_window(mlx_w.mlx,mlx_w.win,mlx_w.img,0,0);
    mlx_loop(mlx_w.mlx);
}