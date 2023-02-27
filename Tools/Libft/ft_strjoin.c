/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:57:03 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/13 10:51:58 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		len_s2;
	size_t		len_s1;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = -1;
	str = (char *)malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (++i < len_s1)
		str[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		str[i + len_s1] = s2[i];
	str[len_s1 + len_s2] = '\0';
	return (str);
}
