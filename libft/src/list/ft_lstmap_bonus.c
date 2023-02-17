/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:12:35 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:54:51 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_ft;
	t_list	*final_lst;

	if (!lst || !f)
		return (NULL);
	final_lst = NULL;
	while (lst != NULL)
	{
		new_ft = ft_lstnew(f(lst->content));
		if (!new_ft)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&final_lst, new_ft);
		lst = lst->next;
	}
	return (final_lst);
}
