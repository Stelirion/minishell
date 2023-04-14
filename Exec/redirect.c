/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:09:48 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/13 15:17:30 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_redirect(t_param *param, int *i)
{
	t_param	*tmp;

	tmp = param;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE)
		{
			i[0] = open(tmp->content, O_RDONLY);
			if (i[0] == -1)
				ft_putstr_fd(strerror(errno), 2);
			else
				dup2(i[0], 0);
			close (i[0]);
		}
		else if (tmp->type == OUTFILE)
		{
			i[1] = open (tmp->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (i[1] == -1)
				ft_putstr_fd(strerror(errno), 2);
			else
				dup2(i[1], 1);
			close (i[1]);
		}
		else if (tmp->type == APPEND)
		{
			i[1] = open (tmp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (i[1] == -1)
				ft_putstr_fd(strerror(errno), 2);
			else
				dup2(i[1], 1);
			close (i[1]);
		}
		tmp = tmp->next;
	}
}

void	ft_undup(int *i)
{
	if (i[0] && i[0] != -2)
		dup2(i[2], 0);
	if (i[1] && i[1] != -2)
		dup2(i[3], 1);
}
