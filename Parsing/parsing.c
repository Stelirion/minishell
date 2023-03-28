/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:01:11 by ngennaro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/28 08:41:28 by ngennaro         ###   ########lyon.fr   */
=======
/*   Updated: 2023/03/28 01:48:19 by mbrement         ###   ########lyon.fr   */
>>>>>>> e2d9faf795537c78a3f128be87895034120bf6b2
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	split_token(char *line, size_t start)
{
	size_t	i;

	i = start;
	while (line[i + 1] != ' ' && line[i + 1])
	{
		i++;
	}
	return (i);
}

char	*manage_quote(char *token)
{
	size_t	i;
	int		type;
	char	*new;

	i = 0;
	type = 0;
	new = malloc(sizeof(char));
	new[0] = '\0';
	while (token[i])
	{
		if (token[i] == '\'' && type == 1)
			type = 0;
		else if (token[i] == '\'' && type == 0)
			type = 1;
		else if (token[i] == '"' && type == 2)
			type = 0;
		else if (token[i] == '"' && type == 0)
			type = 2;
		else
			new = ft_straddback(new, token[i]);
		i++;
	}
	if (type != 0)
		return (free (new),free (token), NULL);
	return (free (token), new);
}

t_param	*parsing_core(char *line, t_param *param)
{
	size_t	i;
	size_t	start;
	char	*next_token;
	t_param	*new_lst;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		i = split_token(line, start);
		next_token = ft_substr(line, start, i + 1 - start);
		next_token = manage_quote(next_token);
		if (!next_token)
			return (free(param), NULL);
		new_lst = param_lstnew(next_token);
		param_lstadd_back(&param, new_lst);
		i++;
	}
	return (param);
}
