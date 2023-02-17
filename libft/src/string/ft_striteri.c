/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:19:05 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/04 17:22:17 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	index;

	index = 0;
	while (s[index])
	{
		f(index, &s[index]);
		index++;
	}
}
