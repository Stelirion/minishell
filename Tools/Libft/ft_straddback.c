/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:21:26 by ngennaro          #+#    #+#             */
/*   Updated: 2023/03/22 04:33:19 by ngennaro         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddback(char const *s1, char const s2)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1 = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = s2;
	i++;
	str[i] = '\0';
	free((void *)s1);
	return (str);
}