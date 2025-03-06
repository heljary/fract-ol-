/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heljary <heljary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 03:14:24 by heljary           #+#    #+#             */
/*   Updated: 2025/03/06 03:47:34 by heljary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	double		result;
    double dicimal;
	
    i = 0;
	sign = 1;
	result = 0;
    dicimal = 1.0;

	if (!str)
		return 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
    if(str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
	    {
            dicimal /=10;
	    	result += (str[i] - '0') * dicimal;
	    	i++;
	    }
    }
	return (result * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if(!s1 || !s2)
		return 0;
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}