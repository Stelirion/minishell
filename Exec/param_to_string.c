/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_to_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:14:28 by mbrement          #+#    #+#             */
/*   Updated: 2023/03/05 17:05:44 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**param_to_array(t_param *param)
{
	char	**str;
	char	*tmp;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char *) * (param_lstsize(param) + 1));
	if (!str)
		error_handler(130);
	while (param)
	{
		tmp = ft_strdup(param->content);
		if (!tmp)
			error_handler(130);
		str[i] = tmp;
		param = param->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}
