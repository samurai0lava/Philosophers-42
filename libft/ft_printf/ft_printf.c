/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouhssei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:11:21 by iouhssei          #+#    #+#             */
/*   Updated: 2023/11/27 10:21:55 by iouhssei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_format(const char format, va_list ap)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(ap, int));
	else if (format == 's')
		len += ft_putstr(va_arg(ap, char *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr_base((long)va_arg(ap, int), 10, 0);
	else if (format == 'x')
		len += ft_putnbr_base((long)va_arg(ap, unsigned int), 16, 0);
	else if (format == 'X')
		len += ft_putnbr_base((long)va_arg(ap, unsigned int), 16, 1);
	else if (format == 'p')
		len += ft_putptr(va_arg(ap, void *));
	else if (format == '%')
		len += ft_putchar('%');
	else if (format == 'u')
		len += ft_putnbr_base((long)va_arg(ap, unsigned int), 10, 0);
	else
		len = 0;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int			i;
	va_list		ap;
	int			count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '\0')
			return (0);
		else if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			count += check_format(format[i + 1], ap);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ap);
	return (count);
}
