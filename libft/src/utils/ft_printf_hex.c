/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:33:38 by aoropeza          #+#    #+#             */
/*   Updated: 2022/06/15 13:40:00 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_tohex(unsigned int nb, char c, int *ptrlen)
{
	int	ch;

	if (nb >= 16)
		ft_tohex(nb / 16, c, ptrlen);
	nb = nb % 16;
	ch = 48;
	if (nb >= 10 && c == 'X')
		ch = 55;
	else if (nb >= 10 && c == 'x')
		ch = 87;
	ft_putchar(nb + ch, ptrlen);
}

void	ft_toptr(unsigned long nb, int *ptrlen)
{
	unsigned long	ch;

	if (nb >= 16)
		ft_toptr(nb / 16, ptrlen);
	nb %= 16;
	ch = 48;
	if (nb >= 10)
		ch = 87;
	ft_putchar(nb + ch, ptrlen);
}
