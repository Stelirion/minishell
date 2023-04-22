/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:40:57 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/22 18:42:35 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_redirect_pipe(t_param **param, int *next, int *tilt)
{
	*tilt = 0;
	if ((*param)->content[0] == '|')
	{
		(*param)->type = PIPE;
		if (!(*param)->next)
			return (parsing_error(2), *tilt = 1, 1);
		*next = 1;
	}
	else
		return (0);
	return (1);
}

int	handle_redirect_in(t_param **param, int *tilt)
{
	if ((*param)->content[0] == '<')
	{
		(*param)->type = 9;
		if (!(*param)->next)
			return (parsing_error(4), *tilt = 1, 1);
		(*param) = (*param)->next;
		if ((*param)->content[0] == '<')
		{
			(*param)->type = 9;
			if (!(*param)->next)
				return (parsing_error(7), *tilt = 1, 1);
			(*param) = (*param)->next;
			(*param)->type = HEREDOC;
		}
		else
			(*param)->type = INFILE;
	}
	else
		return (0);
	return (1);
}

int	handle_redirect_out(t_param **param, int *tilt)
{
	if ((*param)->content[0] == '>')
	{
		(*param)->type = 9;
		if (!(*param)->next)
			return (parsing_error(4), *tilt = 1, 1);
		(*param) = (*param)->next;
		if ((*param)->content[0] == '>')
		{
			(*param)->type = 9;
			if (!(*param)->next)
				return (parsing_error(8), *tilt = 1, 1);
			(*param) = (*param)->next;
			(*param)->type = APPEND;
		}
		else
			(*param)->type = OUTFILE;
	}
	else
		return (0);
	return (1);
}

int	handler_type_command(t_param **param, int *next)
{
	if (*next == 1)
	{
		(*param)->type = CMD;
		*next = 0;
	}
	else
		return (0);
	return (1);
}
