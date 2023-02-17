/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:39:24 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/06 20:50:13 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*empty;

	if (nitems == __SIZE_MAX__ && size > 1)
		return (NULL);
	else if (nitems > 1 && size == __SIZE_MAX__)
		return (NULL);
	else
	{
		empty = malloc(nitems * size);
		if (empty == NULL)
			return (NULL);
		ft_bzero(empty, nitems * size);
		return (empty);
	}
}
