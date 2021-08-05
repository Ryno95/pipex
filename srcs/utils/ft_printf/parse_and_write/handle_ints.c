/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_ints.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 15:19:41 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:23:32 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	handle_num(int num, t_flags *fmtg)
{
	char		*str;
	int			ret;
	long long	nbr;

	ret = 0;
	nbr = num;
	if (nbr < 0)
	{
		fmtg->is_neg = 1;
		nbr *= -1;
		fmtg->width -= 1;
	}
	str = num_converter(nbr, 10);
	if (fmtg->is_precision && fmtg->prec_len == 0 && num == 0)
		ret += print_string("", fmtg);
	else
		ret += print_num(str, fmtg);
	return (ret);
}

int	nbr_right_align(char *str, t_flags *fmtg)
{
	int	ret;
	int	len;

	ret = 0;
	len = ft_strlen(str);
	if (fmtg->is_neg)
		ret += write(1, "-", 1);
	if (fmtg->is_zero)
		ret += write_zero(fmtg->width - len);
	else if (fmtg->prec_len > len)
		ret += write_zero(fmtg->prec_len - len);
	ret += write(1, str, len);
	if (fmtg->is_precision && fmtg->width && len < fmtg->prec_len)
		ret += write_space(fmtg->width - fmtg->prec_len);
	else
		ret += write_space(fmtg->width - len);
	return (ret);
}

int	nbr_left_align(char *str, t_flags *fmtg)
{
	int	ret;
	int	len;

	ret = 0;
	len = ft_strlen(str);
	if (fmtg->is_precision && fmtg->width && len < fmtg->prec_len)
		ret += write_space(fmtg->width - fmtg->prec_len);
	else if (fmtg->width && !fmtg->is_zero)
		ret += write_space(fmtg->width - len);
	if (fmtg->is_neg)
		ret += write(1, "-", 1);
	if (fmtg->is_zero && fmtg->width > len)
		ret += write_zero(fmtg->width - len);
	else if (fmtg->is_precision && fmtg->prec_len > len)
		ret += write_zero(fmtg->prec_len - len);
	ret += write(1, str, len);
	return (ret);
}

int	print_num(char *str, t_flags *fmtg)
{
	int	ret;

	ret = 0;
	if (fmtg->is_minus)
		ret += nbr_right_align(str, fmtg);
	else
		ret += nbr_left_align(str, fmtg);
	return (ret);
}

int	print_unsigned(unsigned int num, t_flags *fmtg)
{
	int		ret;
	char	*str;

	ret = 0;
	str = num_converter(num, 10);
	if (fmtg->is_precision && fmtg->prec_len == 0 && num == 0)
		ret += print_string("", fmtg);
	else
		ret += print_num(str, fmtg);
	return (ret);
}
