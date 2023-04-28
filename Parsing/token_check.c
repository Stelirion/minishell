/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:48:31 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/28 13:58:38 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	format_handler(char *line, int *i, int *pipe, int *redirect)
{
	if (line[*i] == '|')
		(*pipe)++;
	else if ((line[*i] == '>' || line[*i] == '<'))
	{
		if (line[(*i) + 1] && line[(*i) + 1] == line[*i])
			(*i)++;
		(*redirect)++;
	}
	else
		return (0);
	return (1);
}

int	token_format(char *line)
{
	int	i;
	int	type;
	int	pipe;
	int	redirect;

	i = 0;
	type = 0;
	pipe = 0;
	redirect = 0;
	while (line[i])
	{
		type = get_status(line[i], type);
		if (pipe > 1 || redirect > 1)
			return (0);
		else if (type == 0 && format_handler(line, &i, &pipe, &redirect))
			;
		else if (ft_isalpha(line[i]))
		{
			pipe = 0;
			redirect = 0;
		}
		i++;
	}
	return (1);
}
