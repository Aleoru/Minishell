/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:35:53 by aoropeza          #+#    #+#             */
/*   Updated: 2022/06/15 13:35:57 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putchar(char c, int *ptrlen)
{
	*ptrlen += write(1, &c, 1);
}

void	ft_putstr(char *s, int *ptrlen)
{
	int	index;

	index = 0;
	if (s == NULL)
		s = "(null)";
	while (s[index])
	{
		ft_putchar(s[index], ptrlen);
		index++;
	}
}

void	ft_putnbr(int n, int *ptrlen)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-', ptrlen);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, ptrlen);
	ft_putchar(nb % 10 + '0', ptrlen);
}

void	ft_putunbr(unsigned int n, int *ptrlen)
{
	long	nb;

	nb = n;
	if (nb > 9)
		ft_putnbr(nb / 10, ptrlen);
	ft_putchar(nb % 10 + '0', ptrlen);
}
