/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:48:31 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/28 13:50:53 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		else if (line[i] == '|' && type == 0)
			pipe++;
		else if ((line[i] == '>' || line[i] == '<') && type == 0)
		{
			if (line[i + 1] && line[i + 1] == line[i])
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