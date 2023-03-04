/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:38:55 by mbrement          #+#    #+#             */
/*   Updated: 2023/02/04 12:05:28 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*swap;
	char	*conv;

	conv = dst;
	swap = (char *)src;
	i = len;
	if (src < dst)
		while (i-- > 0)
			conv[i] = swap[i];
	else
		ft_memcpy (dst, src, len);
	return (dst);
}
