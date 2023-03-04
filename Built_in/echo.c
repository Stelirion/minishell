/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:34:28 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/04 13:39:21 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	self_check_old(char	*str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == ' ')
			j++;
		if (str[i + j] != '-')
			return (i + j);
		else
			j++;
		if (str[i + j] != 'n')
			return (i);
		while (str[i + j] && str[i + j] == 'n')
			j++;
		if (str[i + j] && str[i + j] != ' ')
			return (i);
		i += j;
	}	
	return (i);
}

static size_t	self_check(char	*str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i + j] != '-')
			return (0);
		else
			j++;
		if (str[i + j] != 'n')
			return (0);
		while (str[i + j] && str[i + j] == 'n')
			j++;
		if (str[i + j] && str[i + j] != ' ')
			return (0);
		i += j;
	}	
	return (1);
}

void	echo_old(char	*str)
{
	size_t	check;
	size_t	i;
	size_t	tmp;

	g_return_value = 0;
	i = -1;
	check = 0;
	tmp = -1;
	if (!str)
		return ((void)write (1, "\n", 1));
	while (str[++tmp] == ' ')
		check = tmp;
	check += self_check_old(str);
	if (check > 0)
		i = check - 1;
	while (str[++i] != '\0')
		ft_putchar_fd(str[i], 1);
	if (check != tmp)
		return ;
	write (1, "\n", 1);
}

void	echo(char	**str)
{
	int		flag;
	size_t	i;

	i = -1;
	flag = 0;
	while (self_check(str[++i]))
		flag = 1;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write (1, "\n", 1);
	g_return_value = 1;
}
