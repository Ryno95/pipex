/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_flags.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/28 20:05:48 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:24:56 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	check_flags(t_flags *flags)
{
	char	*ptr;
	int		i;

	ptr = flags->format;
	i = 0;
	while (ptr[i] != '\0' && ft_strchr(ALL_FLAGS, ptr[i]))
	{
		if (ptr[0] == '0' && flags->is_zero == 0)
			flags->is_zero = 1;
		else if (ft_strchr("csdipxXu%", ptr[i]))
			flags->type = ptr[i];
		else if (ptr[i] == '.')
			flags->is_precision = 1;
		else if (ptr[i] == '-')
			flags->is_minus = 1;
		if (ptr[i] == '%')
			break ;
		i++;
	}
	if (flags->is_minus && flags->is_zero)
		flags->is_zero = 0;
}

static int	handle_precision(va_list ap, t_flags *flags)
{
	char	*ptr;
	int		i;

	ptr = flags->format;
	i = 0;
	if (ptr[i] == '.')
	{
		i++;
		if (ptr[i] == '*')
		{
			flags->prec_len = va_arg(ap, int);
			if (flags->prec_len < 0)
				flags->is_precision = 0;
			i++;
		}
		else if (ft_isdigit(ptr[i]))
		{
			flags->prec_len = ft_atoi(&ptr[i]);
			while (ft_isdigit(ptr[i]))
				i++;
		}
	}
	return (i);
}

static int	handle_width(va_list ap, t_flags *flags)
{
	char	*ptr;
	int		i;

	ptr = flags->format;
	i = 0;
	while (ft_strchr("0-", ptr[i]))
		i++;
	if (ptr[i] == '*')
	{
		flags->width = va_arg(ap, int);
		if (flags->width < 0)
		{
			flags->width *= -1;
			flags->is_minus = 1;
		}
		i++;
	}
	else
	{
		flags->width = ft_atoi(&ptr[i]);
		while (ft_isdigit(ptr[i]))
			i++;
	}
	return (i);
}

int	handle_flags(va_list ap, t_flags *flags)
{
	check_flags(flags);
	flags->format += handle_width(ap, flags);
	if (flags->is_precision == 1)
		flags->format += handle_precision(ap, flags);
	if (ft_strchr("xXuid", flags->type) && flags->is_precision)
		flags->is_zero = 0;
	if (flags->is_zero && flags->is_minus)
		flags->is_zero = 0;
	return (handle_type(ap, flags));
}
