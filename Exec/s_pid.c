/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_pid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:31:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/22 21:57:51 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pid_clear(t_pid *pid)
{
	t_pid	*tmp;

	while (pid)
	{
		tmp = pid;
		pid = pid->next;
		if (tmp)
		{
			if (tmp->pid)
				free(tmp->pid);
			free(tmp);
		}
	}
	free(pid);
}

void	pid_lstadd_back(t_pid **pid, t_pid *next)
{
	t_pid	*last;

	if (!next || !pid)
		return ;
	if (!*pid)
	{
		*pid = next;
		return ;
	}
	last = *pid;
	while (last)
	{
		if (last->next == NULL)
		{
			last->next = next;
			return ;
		}
		last = last->next;
	}
}

t_pid	*pid_lstnew(int pid)
{
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	if (!new)
		return (NULL);
	if (pid)
	{
		new->pid = malloc(sizeof(int));
		if (!new->pid)
			return (free(new), NULL);
		new->pid[0] = pid;
	}
	else
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

void	waiting(t_pid *pid)
{
	t_pid	*tmp;

	tmp = pid;
	while (tmp)
	{
		if (tmp->pid && tmp->pid [0] && tmp->pid[0] > 0)
		{
			waitpid(tmp->pid[0], &g_return_value, 0);
			if (WIFEXITED(g_return_value))
				g_return_value = WEXITSTATUS(g_return_value);
			else if (WIFSIGNALED(g_return_value))
			{
				if (WTERMSIG(g_return_value) == 13)
					g_return_value = 0;
				else
					g_return_value = 128 + WTERMSIG(g_return_value);
			}			
		}
		tmp = tmp->next;
	}
	pid_clear(pid);
}
