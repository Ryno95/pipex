/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/28 19:31:12 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:21:16 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	bzerostruct(t_flags *list)
{
	list->write_count = 0;
	list->is_minus = 0;
	list->is_zero = 0;
	list->is_precision = 0;
	list->width = 0;
	list->prec_len = 0;
	list->is_neg = 0;
}

void	write_width_zero_space(t_flags *fmtg, int len)
{
	if (len < fmtg->width)
	{
		if (fmtg->is_zero)
			write_zero(fmtg->width - len);
		else
			write_space(fmtg->width - len);
	}
}

char	*num_converter(long long nbr, int base)
{
	static char	num_rep[] = "0123456789";
	static char	buffer[25];
	char		*ptr;

	ptr = &buffer[24];
	*ptr = '\0';
	if (nbr == 0)
	{
		--ptr;
		*ptr = '0';
	}
	else if (nbr < 0)
		nbr *= -1;
	while (nbr != 0)
	{
		--ptr;
		*ptr = num_rep[nbr % base];
		nbr /= base;
	}
	return (ptr);
}

int	write_zero(int len)
{
	int	ret;

	ret = 0;
	while (len > 0)
	{
		ret += write(1, "0", 1);
		len--;
	}
	return (ret);
}

int	write_space(int len)
{
	int	ret;

	ret = 0;
	while (len > 0)
	{
		ret += write(1, " ", 1);
		len--;
	}
	return (ret);
}
