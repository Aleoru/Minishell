/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:25:39 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/04 17:31:20 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	while (s[index])
	{
		write(fd, &s[index], 1);
		index++;
	}
}
