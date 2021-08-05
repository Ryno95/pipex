/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_str_and_chrs.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/03 13:47:35 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:25:19 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_char(int c, t_flags *fmtg)
{
	int	ret;

	ret = 0;
	if (fmtg->is_minus)
		ret += write(1, &c, 1);
	if (fmtg->width > 1 && !fmtg->is_zero)
		ret += write_space(fmtg->width - 1);
	else if (fmtg->type == '%' && fmtg->width > 1)
		ret += write_zero(fmtg->width - 1);
	if (!fmtg->is_minus)
		ret += write(1, &c, 1);
	return (ret);
}

int	print_string(char *str, t_flags *fmtg)
{
	int	len;
	int	ret;

	if (!str)
		return (print_string("(null)", fmtg));
	len = ft_strlen(str);
	if (fmtg->is_precision && fmtg->prec_len <= len)
		len = fmtg->prec_len;
	ret = 0;
	if (fmtg->is_minus)
		write(1, str, len);
	write_width_zero_space(fmtg, len);
	if (len < fmtg->width)
		ret += len + (fmtg->width - len);
	else
		ret += len;
	if (!fmtg->is_minus)
		write(1, str, len);
	return (ret);
}
