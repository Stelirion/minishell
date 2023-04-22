/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:34:28 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 19:42:48 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	self_check(char	*str)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str || !str[i])
		return (0);
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

void	echo(char	**str)
{
	int		flag;
	size_t	i;

	i = 0;
	flag = 0;
	if (!str || !str[0])
	{
		write (1, "\n", 1);
		return ;
	}
	while (self_check(str[i]))
	{
		flag = 1;
		i++;
	}
	while (str[i] && str[i][0] != '\0')
	{
		ft_putstr_fd(str[i], 1);
		write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write (1, "\n", 1);
	g_return_value = 0;
}

int	echo_built_int(t_param	*param, t_env *env)
{
	char	**str;

	str = param_to_arg(env, param->next);
	if (!str)
		str[1] = ft_strdup("");
	echo(str);
	free_tab(str);
	return (-2);
}
