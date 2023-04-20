/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tab_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:05:03 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/20 22:24:27 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **str);


char	*merge_tab_char(char **str)
{
	char	*rtn;
	char	*tmp;
	size_t	i;

	rtn = ft_strjoin("\0", str[0]);
	i = 0;
	while (str[++i])
	{
		tmp = ft_strdup(rtn);
		free(rtn);
		rtn = ft_strjoin(tmp, str[i]);
		free(tmp);
	}
	return (rtn);
}

char	*merge_tab_char_add(char **str, char *c)
{
	char	*rtn;
	char	*tmp;
	size_t	i;

	rtn = ft_strjoin("\0", str[0]);
	i = 0;
	while (str[++i])
	{
		tmp = ft_strjoin(rtn, c);
		free(rtn);
		rtn = ft_strjoin(tmp, str[i]);
		free(tmp);
	}
	free_tab(str);
	return (rtn);
}

char	*merge_tab_char_add_minus(char **str, char *c)
{
	char	*rtn;
	char	*tmp;
	size_t	i;

	rtn = ft_strdup(str[0]);
	i = 1;
	while (str[i + 1] && str[i])
	{
		tmp = ft_strjoin(rtn, c);
		free(rtn);
		rtn = ft_strjoin(tmp, str[i]);
		free(tmp);
		i++;
	}
	if (!str[1])
	{
		free(rtn);
		rtn = ft_strdup("/");
	}
	free_tab(str);
	return (rtn);
}
