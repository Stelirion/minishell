/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 08:51:30 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/05 19:41:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_status(char token, int type)
{
	printf("%c|%i\n", token, type);
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
		//else if (token[i] == '$' && type != 1)
		//	new = new + value dans l'env (si pas d'env free all et return error)
		else
			new = ft_straddback(new, token[i]);
		i++;
	}
	if (type != 0)
		return (free (new), free (token), NULL);
	return (free (token), new);
}

t_param	*parsing_core(char *line, t_param *param)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*next_token;
	t_param	*new_lst;

	i = 0;
	len = ft_strlen(line);
	while (i <= len)
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		i = split_token(line, start);
		next_token = ft_substr(line, start, i - start);
		printf("%s, split\n\n", next_token);
		next_token = manage_quote(next_token);
		if (!next_token)
			return (free(param), NULL);
		new_lst = param_lstnew(next_token);
		param_lstadd_back(&param, new_lst);
	}
	return (param);
}
