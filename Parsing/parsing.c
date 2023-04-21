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
	while (line[i])
	{
		type = get_status(line[i], type);
		if (symbol > 1)
			return (0);
		else if (line[i] == '|')
			symbol++;
		else if (line[i] == '<')
		{
			if (line[i + 1] && line[i + 1] == '<')
				i++;
			symbol++;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				i++;
			symbol++;
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

size_t	replace_value(size_t i, char **new, char *token, t_env *env)
{
	char	*to_change;
	t_env	*env_value;

	to_change = 0;
	env_value = NULL;
	while (token[i])
	{
		i++;
		if (token[i] == '"' || token[i] == ' '
			|| token[i] == '<' || token[i] == '>' || token[i] == '|')
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
		return (parsing_error(1), free(*new), 0);
	*new = ft_strjoin_free(*new, env_value->content);
	return (i - 1);
}

char	*manage_quote(char *token, t_env *env)
{
	size_t	i;
	int		type;
	char	*new;

	i = 0;
	type = 0;
	new = malloc(sizeof(char));
	if (!new)
		return (NULL);
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
		else if (token[i] == '$' && type != 1)
		{
			i = replace_value(i, &new, token, env);
			if (!i)
				return (free(token), NULL);
		}
		else
			new = ft_straddback(new, token[i]);
		i++;
	}
	if (type != 0)
		return (parsing_error(3), free(new), free(token), NULL);
	return (free(token), new);
}

t_param	*parsing_core(char *line, t_param *param, t_env	*env)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*next_token;
	t_param	*new_lst;

	i = 0;
	len = ft_strlen(line);
	if (token_format(line) == 0)
		return (parsing_error(6), free(param), NULL);
	while (i <= len)
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		i = split_token(line, start);
		next_token = ft_substr(line, start, i - start);
		if (!next_token)
			return (parsing_error(0), free(param), NULL);
		next_token = manage_quote(next_token, env);
		if (!next_token)
			return (param_lstclear(&	param), NULL);
		new_lst = param_lstnew(next_token);
		param_lstadd_back(&param, new_lst);
	}
	return (param);
}
