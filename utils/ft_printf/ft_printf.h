/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/28 19:31:32 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/06 19:19:31 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define TYPES "csdixXpu"
# define FORMATS "0123456789.-*%"
# define ALL_FLAGS "0123456789.-*csdixXpu%"

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_printf_flags
{
	char	*format;
	int		write_count;

	int		is_minus;
	int		is_zero;
	int		width;

	int		is_precision;
	int		prec_len;

	int		is_neg;

	char	type;
}				t_flags;

char			*ft_strchr(const char *s, int c);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);

int				ft_printf(const char *format, ...);

void			bzerostruct(t_flags *list);

char			*num_converter(long long nbr, int base);
void			write_width_zero_space(t_flags *fmtg, int len);
int				write_zero(int len);
int				write_space(int len);

int				handle_type(va_list ap, t_flags *flags);

int				handle_flags(va_list ap, t_flags *flags);

char			*hexa_converter(unsigned long long num, int base, char c);
int				print_hexa(long long num, t_flags *fmtg, char c);
int				print_address(void *ptr, t_flags *fmtg);

int				print_string(char *str, t_flags *fmtg);
int				print_char(int c, t_flags *fmtg);

int				nbr_right_align(char *str, t_flags *fmtg);
int				nbr_left_align(char *str, t_flags *fmtg);
int				handle_num(int num, t_flags *fmtg);
int				print_num(char *str, t_flags *fmtg);
int				print_unsigned(unsigned int num, t_flags *fmtg);

#endif
