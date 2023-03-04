/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:31:34 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/15 16:31:17 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*str;

	str = s1;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(""));
	while (*s1)
		if (!ft_strchr(set, *s1++))
			break ;
	s1--;
	start = s1;
	while (*s1)
		++s1;
	--s1;
	while (*s1)
		if (s1 <= str || !ft_strchr(set, *s1--))
			break ;
	if (s1 + 2 <= start)
		return (ft_strdup(""));
	return (ft_substr(start, 0, s1 - start + 2));
}
