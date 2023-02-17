/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:01:07 by aoropeza          #+#    #+#             */
/*   Updated: 2022/05/10 18:11:25 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	num;
	int	sign;

	index = 0;
	num = 0;
	sign = 1;
	while (str[index] == ' ' || str[index] == '\f' || str[index] == '\n'
		|| str[index] == '\r' || str[index] == '\t' || str[index] == '\v')
		index++;
	if (str[index] == '-')
	{
		sign = sign * -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	if (!ft_isdigit(str[index]))
		return (0);
	while (ft_isdigit(str[index]))
	{
		num = (num * 10) + str[index] - '0';
		index++;
	}
	return (num * sign);
}
