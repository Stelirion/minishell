/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:14:30 by mbrement          #+#    #+#             */
/*   Updated: 2022/11/08 15:31:38 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset( void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	chr;

	str = b;
	chr = c;
	i = -1;
	while (++i < len)
		str[i] = chr;
	return (b);
}
