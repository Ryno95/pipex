/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_type.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/28 19:58:08 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:23:53 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	handle_type(va_list ap, t_flags *fmtg)
{
	char	*frmt;
	int		count;

	frmt = fmtg->format;
	count = 0;
	if (*frmt == '%')
		count += print_char('%', fmtg);
	else if (*frmt == 'c')
		count += print_char(va_arg(ap, int), fmtg);
	else if (*frmt == 's')
		count += print_string(va_arg(ap, char *), fmtg);
	else if (*frmt == 'd' || *frmt == 'i')
		count += handle_num(va_arg(ap, int), fmtg);
	else if (*frmt == 'p')
		count += print_address(va_arg(ap, void *), fmtg);
	else if (*frmt == 'x' || *frmt == 'X')
		count += print_hexa(va_arg(ap, unsigned int), fmtg, *frmt);
	else if (*frmt == 'u')
		count += print_unsigned(va_arg(ap, unsigned int), fmtg);
	return (count);
}
