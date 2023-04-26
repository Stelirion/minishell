/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:21:26 by ngennaro          #+#    #+#             */
/*   Updated: 2023/04/26 16:36:44 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_straddback(char *s1, char const s2)
{
	int		i;
	char	*str;

	i = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		*s1 = 0;
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = s2;
	i++;
	str[i] = '\0';
	return (free(s1), str);
}
