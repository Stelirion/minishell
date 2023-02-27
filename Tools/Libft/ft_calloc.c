/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:55:22 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/17 18:15:45 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (size > 0 && count >= SIZE_MAX / size)
		return (NULL);
	dst = malloc(count * size);
	if (dst == NULL)
		return (NULL);
	ft_bzero(dst, count * size);
	return (dst);
}
