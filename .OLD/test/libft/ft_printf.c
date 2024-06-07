/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:47:28 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 17:28:54 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_process_format(const char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 'd' || *format == 'i')
		count += ft_putnbr_rlen(va_arg(args, int), 0);
	else if (*format == 'u')
		count += ft_putnbr_unsigned_rlen(va_arg(args, unsigned int), 0);
	else if (*format == '%')
		count += ft_putchar('%');
	else if (*format == 'c')
		count += ft_putchar((char)va_arg(args, int));
	else if (*format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*format == 'x' || *format == 'X')
		count += ft_putnbr_hex_rlen(va_arg(args, unsigned int), 0, *format);
	else if (*format == 'p')
		count += ft_putptr_rlen(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_process_format(format, args);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (count);
}

/* int main(void)
{
    int count;
    int originalcount;

    count = 0;
    originalcount = 0;
    count = ft_printf("\n%sVersion::%s %%T ESTdsadsadsad %d - char %c - "
	"percentage %% - unsigned %u - hex %X - pointer %p\n", 
	KCYN, KNRM, -678, 'f', 3213213, 3213213, (void*)0);
    originalcount = printf("\n%sOriginal:%s %%T ESTdsadsadsad %d - "
	"char %c - percentage %% - unsigned %u - hex %X - pointer %p\n", 
	KCYN, KNRM, -678, 'f', 3213213, 3213213, (void*)0);
    if(originalcount == count)
    {
        ft_printf("\n%sOK>> %s Result for both is = %d\n", 
		KGRN, KNRM, originalcount);
    }
    else 
    {
        ft_printf("\n%sERR> %s Result ft = %d / Original is %d\n", 
		KRED, KNRM, count, originalcount);
    }
    return (0);
} */