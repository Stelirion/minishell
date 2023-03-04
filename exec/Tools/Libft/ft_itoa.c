/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:16:44 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/03 13:06:07 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_itoa(char *str, int i, int n)
{
	int	j;

	j = n;
	i--;
	str[i] = '\0';
	if (n == INT32_MIN)
	{
		i--;
		str[i] = 8 + 48;
		n = n / 10;
	}
	if (n < 0 && n != INT32_MIN)
		n *= -1;
	while (--i >= 0)
	{
		str[i] = (n % 10) + 48;
		n /= 10;
	}
	if (j < 0)
		str[0] = '-';
	return (str);
}

static char	*ft_exept_itoa(int n)
{
	char	*str;

	if (n == INT32_MIN)
	{
		str = (char *)malloc(sizeof(char) * 12);
		if (!str)
			return (NULL);
		str = ft_fill_itoa(str, 12, n);
		return (str);
	}
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str = ft_fill_itoa(str, 2, n);
		return (str);
	}
	return (NULL);
}

char	*ft_itoa(int n)
{	
	int		i;
	int		j;
	char	*str;

	i = 1;
	if (n == INT32_MIN || n == 0)
		return (ft_exept_itoa(n));
	if (n < 0)
		i++;
	j = n;
	while (j >= 1 || j <= -1)
	{
		i++;
		j = j / 10;
	}
	str = (char *)malloc(sizeof(char) * i);
	if (!str)
		return (NULL);
	str = ft_fill_itoa (str, i, n);
	return (str);
}
