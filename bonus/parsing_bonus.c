/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 01:39:42 by heljary           #+#    #+#             */
/*   Updated: 2025/03/13 01:56:06 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

void	is_not_digit(char **param, int i, int j)
{
	if (!ft_isdigit(param[i][j]))
	{
		ft_putstr("Anvalid argument ...\n");
		exit(0);
	}
}

int	check_param(char **param)
{
	int (i), (found_poin), (found_moin_plus), (j);
	i = 2;
	while (param[i])
	{
		j = 0;
		found_poin = 0;
		found_moin_plus = 0;
		while (param[i][j])
		{
			if ((param[i][j] == '.') && (!found_poin))
			{
				found_poin = 1;
				j++;
			}
			if ((param[i][0] == '+' || param[i][0] == '-') && !found_moin_plus)
			{
				found_moin_plus = 1;
				j++;
			}
			is_not_digit(param, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	double		num_1;
	double		num_2;

	num_1 = ft_atoi(av[2]);
	num_2 = ft_atoi(av[3]);
	if (ft_strcmp(av[1], "mandelbrot") == 0 && ac == 2)
		mandelbrot_window();
	else if (ft_strcmp(av[1], "julia") == 0 && ac == 4)
	{
		if (check_param(av))
			return (1);
		julia_window(num_1, num_2);
	}
	else if (ft_strcmp(av[1], "cmandelbrot") == 0 && ac == 2)
		cubic_mandelbrot_window();
	else
		exit(0);
}
