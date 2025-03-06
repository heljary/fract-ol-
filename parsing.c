/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:14:18 by heljary           #+#    #+#             */
/*   Updated: 2025/03/06 03:47:58 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "fractol.h"

int main(int ac, char **av)
{
    double num_1 = ft_atoi(av[2]);
    double num_2 = ft_atoi(av[3]);
    if(ac == 1)
        exit(0);
    if(ft_strcmp(av[1], "mandelbrot") == 0 && ac == 2)
        mandelbrot_window();
    else if (ft_strcmp(av[1], "julia") == 0 && ac == 4)
        julia_window(num_1,num_2);
    else
        exit(0);
}