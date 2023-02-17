/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:40:07 by aoropeza          #+#    #+#             */
/*   Updated: 2022/06/17 12:08:37 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	check_conversion(char ch, va_list args, int	*ptrlen)
{
	if (ch == 'c')
		ft_putchar((char)va_arg(args, int), ptrlen);
	if (ch == 's')
		ft_putstr(va_arg(args, char *), ptrlen);
	if (ch == 'p')
	{
		ft_putstr("0x", ptrlen);
		ft_toptr(va_arg(args, long), ptrlen);
	}
	if (ch == 'd' || ch == 'i')
		ft_putnbr(va_arg(args, int), ptrlen);
	if (ch == 'u')
		ft_putunbr(va_arg(args, unsigned int), ptrlen);
	if (ch == 'x' || ch == 'X')
		ft_tohex(va_arg(args, int), ch, ptrlen);
	if (ch == '%')
		ft_putchar('%', ptrlen);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		index;
	int		len;
	int		*ptrlen;

	index = 0;
	len = 0;
	ptrlen = &len;
	va_start(args, str);
	while (str[index] != '\0')
	{
		if (str[index] == '%')
		{
			index++;
			check_conversion(str[index], args, ptrlen);
		}
		else
			ft_putchar(str[index], ptrlen);
		index++;
	}
	va_end(args);
	return (len);
}
