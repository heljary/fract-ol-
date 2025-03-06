/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:14:04 by heljary           #+#    #+#             */
/*   Updated: 2025/03/06 03:38:18 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define height  900
#define width   800


void put_pixel(t_mlx *mlx_s, int x, int y, int color)
{
    int offset;
    if (x < 0 || y < 0  || x >= width || y >= height)
        return;

    offset = (y * mlx_s->line_len) + (x * (mlx_s->bpp / 8));
    *(int *)(mlx_s->addr + offset) = color;
}

int RGB(int i)
{
    int red = (i * 20) % 256;  
    int green = (i * 0) % 256;  
    int blue = (i * 0) % 256;  
    return (red * 256) + (green) + (blue);
}

void design_mndlbrt(t_mlx *mlx_w,t_graph *grap)
{
    double Cy;
    double Cx;
    double x  = 0.0;
    double y = 0.0;
    double zx;
    double zx_next;
    double zy;
    double zy_next;
    int iteration  = 0;
    int max_iteration = 100;

    while(y < height)
    {
        Cy = grap->y_min + (y / height) * (grap->y_max - grap->y_min);
        x = 0;
        while (x < width)
        {
            Cx = grap->x_min + (x / width) * (grap->x_max - grap->x_min);
            zx = 0.0;
            zy = 0.0;
            iteration = 0;
            while(zx * zx + zy * zy < 4 && iteration < max_iteration)
            {
                zx_next = zx * zx - zy * zy + Cx;
                zy_next = 2 * zx * zy + Cy;

                zx = zx_next;
                zy = zy_next;
                iteration++;
            }
            if(iteration >= max_iteration)
                put_pixel(mlx_w,x,y,0x000000);
            else
                put_pixel(mlx_w,x,y,RGB(iteration));
            x++;
        }
        y++;
    }
}


int close_window(t_mlx *mlx_w)
{
    mlx_destroy_image(mlx_w->mlx, mlx_w->img);
    mlx_destroy_window(mlx_w->mlx, mlx_w->win);
    mlx_destroy_display(mlx_w->mlx);
    free(mlx_w->mlx);
    exit(0);
}

void zoom_in(t_graph *graph)
{
    double x_center = 0;
    double y_center = 0;

    graph->x_min = x_center - (graph->x_max - graph->x_min) * 0.3;
    graph->x_max = x_center + (graph->x_max - graph->x_min) * 0.3;
    graph->y_min = y_center - (graph->y_max - graph->y_min) * 0.3;
    graph->y_max = y_center + (graph->y_max - graph->y_min) * 0.3;
}

void zoom_out(t_graph *graph)
{
    double x_center = 0;
    double y_center = 0; 

    graph->x_min = x_center - (graph->x_max - graph->x_min) * 1 / 0.3; 
    graph->x_max = x_center + (graph->x_max - graph->x_min) * 1 / 0.3; 
    graph->y_min = y_center - (graph->y_max - graph->y_min) * 1 / 0.3;
    graph->y_max = y_center + (graph->y_max - graph->y_min) * 1 / 0.3; 
}

int mouse_hook(int button, int x, int y, t_mlx *mlx_w)
{
    (void)x;
    (void)y;

    if (button == 4)
    {
        zoom_in(&mlx_w->graph); 
        design_mndlbrt(mlx_w, &mlx_w->graph);
    }
    else if (button == 5)
    {
        zoom_out(&mlx_w->graph); 
        design_mndlbrt(mlx_w, &mlx_w->graph);
    }
    mlx_put_image_to_window(mlx_w->mlx, mlx_w->win, mlx_w->img, 0, 0);
    return 0;
}

int handle_key(int keycode, t_mlx *mlx_w)
{
    if (keycode == 65362)
    {
        mlx_w->graph.y_min -= 0.1;
        mlx_w->graph.y_max -= 0.1;
    }
    else if (keycode == 65364)
    {
        mlx_w->graph.y_min += 0.1;
        mlx_w->graph.y_max += 0.1;
    }
    else if (keycode == 65361)
    {
        mlx_w->graph.x_min -= 0.1;
        mlx_w->graph.x_max -= 0.1;
    }
    else if (keycode == 65363)
    {
        mlx_w->graph.x_min += 0.1;
        mlx_w->graph.x_max += 0.1;
    }

    design_mndlbrt(mlx_w, &mlx_w->graph);
    mlx_put_image_to_window(mlx_w->mlx, mlx_w->win, mlx_w->img, 0, 0);

    return 0;
}

void mandelbrot_window()
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
    design_mndlbrt(&mlx_w,&mlx_w.graph);
    mlx_hook(mlx_w.win, 2, 1L << 0, handle_key, &mlx_w);
    mlx_mouse_hook(mlx_w.win,mouse_hook,&mlx_w);
    mlx_put_image_to_window(mlx_w.mlx,mlx_w.win,mlx_w.img,0,0);
    mlx_hook(mlx_w.win,17,0,close_window,&mlx_w);
    mlx_loop(mlx_w.mlx);
}