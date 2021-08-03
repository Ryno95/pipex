/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_hexa_and_ptr.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/12 21:55:20 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:22:40 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*hexa_converter(unsigned long long num, int base, char c)
{
	static char	uppercase[] = "0123456789ABCDEF";
	static char	lowercase[] = "0123456789abcdef";
	static char	buffer[50];
	char		*ptr;

	ptr = &buffer[49];
	*ptr = '\0';
	if (num == 0)
	{
		ptr--;
		*ptr = '0';
	}
	while (num != 0)
	{
		ptr--;
		if (c == 'X')
			*ptr = uppercase[num % base];
		else
			*ptr = lowercase[num % base];
		num /= base;
	}
	return (ptr);
}

int	print_hexa(long long num, t_flags *fmtg, char c)
{
	int		ret;
	char	*str;

	ret = 0;
	str = hexa_converter(num, 16, c);
	if (fmtg->is_precision && fmtg->prec_len == 0 && num == 0)
		ret += print_string("", fmtg);
	else
		ret += print_num(str, fmtg);
	return (ret);
}

int	print_address(void *ptr, t_flags *fmtg)
{
	unsigned long long	address;
	char				*pointer;

	if (!ptr && fmtg->prec_len == 0 && fmtg->is_precision)
		return (print_num("0x", fmtg));
	else if (!ptr)
		return (print_num("0x0", fmtg));
	address = (unsigned long long)ptr;
	pointer = hexa_converter(address, 16, 'x');
	pointer--;
	*pointer = 'x';
	pointer--;
	*pointer = '0';
	return (print_num(pointer, fmtg));
}
