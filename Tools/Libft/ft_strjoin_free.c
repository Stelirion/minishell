/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:21:26 by ngennaro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/28 07:55:25 by ngennaro         ###   ########lyon.fr   */
=======
/*   Updated: 2023/03/28 00:29:24 by mbrement         ###   ########lyon.fr   */
>>>>>>> e2d9faf795537c78a3f128be87895034120bf6b2
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
<<<<<<< HEAD
		i++;
		j++;
=======
		j ++;
		i ++;
>>>>>>> e2d9faf795537c78a3f128be87895034120bf6b2
	}
	str[i] = '\0';
	free((void *)s1);
	return (str);
}