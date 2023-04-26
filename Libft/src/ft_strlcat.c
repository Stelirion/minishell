/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:59:00 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/12 11:43:22 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if ((!dstsize && !dst) || (!dstsize && !src))
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize < len_dst)
		return (dstsize + len_src);
	if (!dstsize)
		return (len_src + len_dst);
	i = 0;
	while (src[i] && (i + len_dst + 1) < dstsize)
	{
		dst[len_dst + i] = src [i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + len_src);
}
