/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:14:30 by mbrement          #+#    #+#             */
/*   Updated: 2023/04/26 16:36:44 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
