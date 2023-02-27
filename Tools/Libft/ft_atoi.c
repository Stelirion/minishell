/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:48:24 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/24 18:39:51 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] == ' ') || ((str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] <= '9') && str[i] >= '0')
	{
		if (res != ((res * 10 + (str[i] - 48) * sign) / 10))
			return (-1);
		res = res * 10 + sign * (str[i] - '0');
		i++;
	}
	return ((int)res);
}
