/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:09:48 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 18:13:28 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_append(t_param *param, int *i, t_param	*tmp);
static int	ft_heredoc(t_param *param, int *i, t_param	*tmp);
static int	ft_outfile(t_param *param, int *i, t_param	*tmp);

int	ft_redirect(t_param *param, int *i)
{
	t_param	*tmp;

	tmp = param;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == INFILE)
		{
			i[0] = open(tmp->content, O_RDONLY);
			if (i[0] == -1)
				return (ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), 0);
			else
				dup2(i[0], 0);
			close (i[0]);
		}
		else if (tmp->type == OUTFILE && ft_outfile(param, i, tmp))
			return (0);
		else if (tmp->type == APPEND && ft_append(param, i, tmp) == 0)
			return (0);
		else if (tmp->type == HEREDOC && ft_heredoc(param, i, tmp) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_undup(int *i)
{
	if (i[0] && i[0] != -2)
		dup2(i[2], 0);
	if (i[1] && i[1] != -2)
		dup2(i[3], 1);
}

static int	ft_append(t_param *param, int *i, t_param	*tmp)
{
	(void)param;
	i[1] = open (tmp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (i[1] == -1)
		return (ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), 0);
	else
		dup2(i[1], 1);
	close (i[1]);
	return (1);
}

static int	ft_heredoc(t_param *param, int *i, t_param	*tmp)
{
	(void)param;
	(void)tmp;
	i[0] = open ("/var/tmp/minishell.tmp", O_RDONLY);
	if (i[0] == -1)
		return (ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), 0);
	else
		dup2(i[0], 0);
	close (i[0]);
	return (1);
}

static int	ft_outfile(t_param *param, int *i, t_param	*tmp)
{
	(void)param;
	i[0] = open(tmp->content, O_RDONLY);
	if (i[0] == -1)
		return (ft_putstr_fd(strerror(errno), 2), write(2, "\n", 1), 0);
	else
		dup2(i[0], 0);
	close (i[0]);
	return (1);
}
