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
	int	symbol;

	i = 0;
	symbol = 0;
	while (line[i] && symbol <= 1)
	{
		type = get_status(line[i], type);
		if (symbol > 1)
			return (0);
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			if ((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>'))
				i++;
			if (++symbol > 1)
				return (0);
		}
		else if (ft_isalpha(line[i]))
			symbol = 0;
		i++;
	}
	return (1);
}

size_t	split_token(char *line, size_t start)
{
	size_t	i;
	int		status;

	i = start;
	status = 0;
	if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		return (i + 1);
	while (line[i])
	{
		status = get_status(line[i], status);
		if (status == 0 && line[i] == ' ')
			return (i);
		if (status == 0 && line[i] == '|')
			return (i);
		if (status == 0 && line[i] == '>')
			return (i);
		if (status == 0 && line[i] == '<')
			return (i);
		i++;
	}
	return (i);
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
		return (parsing_error(1), free(*new), -1);
	*new = ft_strjoin_free(*new, env_value->content);
	return (i - 1);
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
		if ((token[i] == '\'' && type == 1) || (token[i] == '"' && type == 2))
			type = 0;
		else if (token[i] == '\'' && type == 0)
			type = 1;
		else if (token[i] == '"' && type == 0)
			type = 2;
		else if (token[i] == '$' && type != 1)
			i = replace_value(i, &new, token, env);
		else if (!(type == 1 && token[i] == '\\'))
			new = ft_straddback(new, token[i]);
		if (!new)
			return (parsing_error(0), free(token), NULL);
		else if (i == -1)
			return (free(token), NULL);
		i++;
	}
	if (type != 0)
		return (parsing_error(3), free(new), free(token), NULL);
	return (free(token), new);
}