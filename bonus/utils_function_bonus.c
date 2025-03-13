/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:14:24 by heljary           #+#    #+#             */
/*   Updated: 2025/03/12 22:16:00 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

double	check_calcul(char *str, int i)
{
	double	dicimal;
	double	result;

	result = 0;
	dicimal = 1.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			dicimal /= 10;
			result += (str[i] - '0') * dicimal;
			i++;
		}
	}
	return (result);
}

double	ft_atoi(char *str)
{
	int		i;
	int		sign;
	double	res;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = check_calcul(str, i);
	return (res * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	rgb(int i)
{
	int	red;
	int	green;
	int	blue;

	red = (i * 10) % 256;
	green = (i * 10) % 256;
	blue = (i * 0) % 256;
	return ((red * 256) + (green * 256) + (blue * 256));
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}
