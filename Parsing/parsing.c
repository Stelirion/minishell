/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:51:30 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/20 00:04:27 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	get_status(char token, int type)
{
	if (token == '\'' && type == 1)
		type = 0;
	else if (token == '\'' && type == 0)
		type = 1;
	else if (token == '"' && type == 2)
		type = 0;
	else if (token == '"' && type == 0)
		type = 2;
	return (type);
}

int	token_format(char *line)
{
	int	i;
	int	type;
	int	pipe;
	int	redirect;

	i = 0;
	pipe = 0;
	redirect = 0;
	while (line[i])
	{
		type = get_status(line[i], type);
		if (pipe > 1 || redirect > 1)
			return (0);
		else if (line[i] == '|')
			pipe++;
		else if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				i++;
			redirect++;
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				i++;
			redirect++;
		}
		else if (ft_isalpha(line[i]))
		{
			pipe = 0;
			redirect = 0;
		}
		i++;
	}
	return (1);
}

ssize_t	replace_value(size_t i, char **new, char *token, t_env *env)
{
	char	*to_change;
	t_env	*env_value;

	to_change = 0;
	env_value = NULL;
	while (token[i])
	{
		i++;
		if (i == 1 && token[i] == '?' && !token[i + 1])
			;
		else if (!ft_isalnum(token[i]) && token[i] != '_')
			break ;
		to_change = ft_straddback(to_change, token[i]);
		if (!to_change)
			return (parsing_error(0), free(*new), 0);
	}
	to_change = ft_straddback(to_change, '=');
	if (!to_change)
		return (parsing_error(0), free(*new), 0);
	env_value = env_search(env, to_change);
	free(to_change);
	if (!env_value)
		return (i - 1);
	*new = ft_strjoin_free(*new, env_value->content);
	return (i - 1);
}

int	handle_quotes(int *type, char c)
{
	if ((c == '\'' && *type == 1) || (c == '"' && *type == 2))
		*type = 0;
	else if (c == '\'' && *type == 0)
		*type = 1;
	else if (c == '"' && *type == 0)
		*type = 2;
	else
		return (0);
	return (1);
}

char	*manage_quote(char *token, t_env *env)
{
	ssize_t	i;
	int		type;
	char	*new;

	i = 0;
	type = 0;
	new = ft_calloc(1, sizeof(char));
	if (!new)
		return (NULL);
	while (token[i])
	{
		if (handle_quotes(&type, token[i]))
			;
		else if (token[i] == '$' && type != 1)
			i = replace_value(i, &new, token, env);
		else if (!(type == 1 && token[i] == '\\'))
			new = ft_straddback(new, token[i]);
		if (i == -1)
			return (free(token), NULL);
		i++;
	}
	if (type != 0)
		return (parsing_error(3), free(new), free(token), NULL);
	return (free(token), new);
}
