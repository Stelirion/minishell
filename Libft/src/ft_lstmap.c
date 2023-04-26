/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:59:32 by mbrement          #+#    #+#             */
/*   Updated: 2023/01/13 12:11:33 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*result;
// 	t_list	*new;

// 	if (!lst || !f || !del)
// 		return (NULL);
// 	result = ft_lstnew(f(lst->content));
// 	if (!result)
// 		return (NULL);
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		new = ft_lstnew(f(lst->content));
// 		if (!new)
// 		{
// 			ft_lstclear (&result, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&result, new);
// 		lst = lst->next;
// 	}
// 	return (result);
// }
