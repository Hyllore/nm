/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:53:32 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 15:46:57 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_printf	field_diese(t_printf *lst, t_flags *lst2)
{
	if (ft_strchr("xX", lst->type) != NULL && lst2->diese == 1 &&
			lst->field > 2 && lst2->zero == 1)
		lst->field -= 2;
	return (*lst);
}

t_printf		apply_flags(t_printf *lst, t_flags *lst2, va_list argptr,
		char *str)
{
	*lst = field_diese(lst, lst2);
	if ((ft_strchr("dDioOuUxX", lst->type)) != NULL && (lst->len_modif[0] != 'h'
				&& lst->len_modif[0] != 'l' && lst->len_modif[0] != 'j' &&
				lst->len_modif[0] != 'z'))
		str = take_type1(lst, lst2, str, argptr);
	if ((ft_strchr("spc", lst->type)) != NULL)
		str = take_type2(lst, str, argptr);
	if (lst->len_modif[0] == 'h' || lst->len_modif[0] == 'l' ||
			lst->len_modif[0] == 'j' || lst->len_modif[0] == 'z')
		str = apply_len_modif(lst, str, argptr, lst2);
	if (lst->field != -1 && lst2->zero == 1 && lst2->minus != 1)
		str = apply_field_zero(lst, lst2, str, ft_strlen(str));
	if (lst->precision >= 0 && (ft_strchr("dDioOuUxX", lst->type)) != NULL)
		str = apply_precision_num(lst, str, ft_strlen(str));
	if (lst2->diese == 1)
		str = apply_diese(lst, str);
	if (lst2->plus == 1)
		str = apply_plus(str);
	if (lst->precision >= 0 && (ft_strchr("sS", lst->type)) != NULL)
		str = apply_precision_str(lst, str);
	if (lst->field != -1 || lst2->zero != 1)
		str = apply_field_space(lst, lst2, str, ft_strlen(str));
	if (lst2->space == 1)
		str = apply_space(str);
	return (write_char(lst, str, 0));
}

t_printf		percent_analysis(const char *format, t_printf *lst)
{
	lst->tmp = lst->i + 1;
	lst->precision = -1;
	lst->field = -1;
	while (ft_strchr("- #*+-.0123456789hljz", format[lst->tmp]) != NULL)
		lst->tmp++;
	if (ft_strchr("%", format[lst->tmp]) != NULL)
	{
		lst->i = lst->i + 1;
		while (format[lst->i] != '%')
		{
			*lst = add_bonus(format, lst);
			lst->i++;
		}
	}
	else
	{
		lst->tmp = 0;
		return (*lst);
	}
	return (apply_percent(lst));
}

t_printf		ft_printf_bis(const char *format, va_list argptr, t_printf *lst)
{
	if (format[lst->i] == '%' && format[lst->i + 1] == '%')
	{
		ft_putchar('%');
		lst->i++;
		lst->i2++;
	}
	else if (format[lst->i] == '%')
	{
		*lst = percent_analysis(format, lst);
		if (lst->tmp == 0)
		{
			lst->i++;
			*lst = seek_types(lst, format, argptr,
					(t_flags*)malloc(sizeof(t_flags)));
			lst->i--;
		}
	}
	else
	{
		ft_putchar(format[lst->i]);
		lst->i2++;
	}
	lst->i++;
	return (*lst);
}

int				ft_printf(const char *format, ...)
{
	va_list		argptr;
	t_printf	*lst;

	lst = (t_printf*)malloc(sizeof(t_printf));
	lst->i = 0;
	lst->i2 = 0;
	va_start(argptr, format);
	while (format[lst->i] != '\0')
	{
		*lst = ft_printf_bis(format, argptr, lst);
	}
	va_end(argptr);
	return (lst->i2);
}
