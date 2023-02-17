/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:05:44 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:15:37 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp(const char *str_one, const char *str_two, size_t n)
{
	unsigned int	index;

	index = 0;
	while ((str_one[index] || str_two[index]) && index < n)
	{
		if (str_one[index] != str_two[index])
			return (((unsigned char *)str_one)[index]
				- ((unsigned char *)str_two)[index]);
		index++;
	}
	return (0);
}
